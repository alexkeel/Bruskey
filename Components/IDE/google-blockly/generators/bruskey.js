'use strict';

goog.provide('Blockly.Bruskey');

goog.require('Blockly.Generator');


/**
 * Bruskey code generator.
 * @type {!Blockly.Generator}
 */
Blockly.Bruskey = new Blockly.Generator('Bruskey');

/**
 * List of illegal variable names.
 * This is not intended to be a security feature.  Blockly is 100% client-side,
 * so bypassing this list is trivial.  This is intended to prevent users from
 * accidentally clobbering a built-in object or function.
 * @private
 */
Blockly.Bruskey.addReservedWords(
    'False,True,and,else,if,else' +
    'for,is,not,equals,function,or,end' +
    'or,while,Pause' +
    'LeftLineDetected,RightLineDetected,ObstacleDetected,Stop,BlobVisible,SpinLeft' +
    'SpinRight,DriveForward,DriveBackward,Pause,GetBlobHAlignment,GetDistance' +
    'double,int,long,char,string,short'
);

/**
 * Order of operation ENUMs.
 * http://docs.python.org/reference/expressions.html#summary
 */
Blockly.Bruskey.ORDER_ATOMIC = 0;            // 0 "" ...
Blockly.Bruskey.ORDER_COLLECTION = 1;        // tuples, lists, dictionaries
Blockly.Bruskey.ORDER_STRING_CONVERSION = 1; // `expression...`
Blockly.Bruskey.ORDER_MEMBER = 2.1;          // . []
Blockly.Bruskey.ORDER_FUNCTION_CALL = 2.2;   // ()
Blockly.Bruskey.ORDER_EXPONENTIATION = 3;    // **
Blockly.Bruskey.ORDER_UNARY_SIGN = 4;        // + -
Blockly.Bruskey.ORDER_BITWISE_NOT = 4;       // ~
Blockly.Bruskey.ORDER_MULTIPLICATIVE = 5;    // * / // %
Blockly.Bruskey.ORDER_ADDITIVE = 6;          // + -
Blockly.Bruskey.ORDER_BITWISE_SHIFT = 7;     // << >>
Blockly.Bruskey.ORDER_BITWISE_AND = 8;       // &
Blockly.Bruskey.ORDER_BITWISE_XOR = 9;       // ^
Blockly.Bruskey.ORDER_BITWISE_OR = 10;       // |
Blockly.Bruskey.ORDER_RELATIONAL = 11;       // in, not in, is, is not,
                                            //     <, <=, >, >=, <>, !=, ==
Blockly.Bruskey.ORDER_LOGICAL_NOT = 12;      // not
Blockly.Bruskey.ORDER_LOGICAL_AND = 13;      // and
Blockly.Bruskey.ORDER_LOGICAL_OR = 14;       // or
Blockly.Bruskey.ORDER_CONDITIONAL = 15;      // if else
Blockly.Bruskey.ORDER_LAMBDA = 16;           // lambda
Blockly.Bruskey.ORDER_NONE = 99;             // (...)

/**
 * List of outer-inner pairings that do NOT require parentheses.
 * @type {!Array.<!Array.<number>>}
 */
Blockly.Bruskey.ORDER_OVERRIDES = [
  // (foo()).bar -> foo().bar
  // (foo())[0] -> foo()[0]
  [Blockly.Bruskey.ORDER_FUNCTION_CALL, Blockly.Bruskey.ORDER_MEMBER],
  // (foo())() -> foo()()
  [Blockly.Bruskey.ORDER_FUNCTION_CALL, Blockly.Bruskey.ORDER_FUNCTION_CALL],
  // (foo.bar).baz -> foo.bar.baz
  // (foo.bar)[0] -> foo.bar[0]
  // (foo[0]).bar -> foo[0].bar
  // (foo[0])[1] -> foo[0][1]
  [Blockly.Bruskey.ORDER_MEMBER, Blockly.Bruskey.ORDER_MEMBER],
  // (foo.bar)() -> foo.bar()
  // (foo[0])() -> foo[0]()
  [Blockly.Bruskey.ORDER_MEMBER, Blockly.Bruskey.ORDER_FUNCTION_CALL],

  // not (not foo) -> not not foo
  [Blockly.Bruskey.ORDER_LOGICAL_NOT, Blockly.Bruskey.ORDER_LOGICAL_NOT],
  // a and (b and c) -> a and b and c
  [Blockly.Bruskey.ORDER_LOGICAL_AND, Blockly.Bruskey.ORDER_LOGICAL_AND],
  // a or (b or c) -> a or b or c
  [Blockly.Bruskey.ORDER_LOGICAL_OR, Blockly.Bruskey.ORDER_LOGICAL_OR]
];

/**
 * Initialise the database of variable names.
 * @param {!Blockly.Workspace} workspace Workspace to generate code from.
 */
Blockly.Bruskey.init = function(workspace) {
  // Create a dictionary of definitions to be printed before the code.
  Blockly.Bruskey.definitions_ = Object.create(null);
  // Create a dictionary mapping desired function names in definitions_
  // to actual function names (to avoid collisions with user functions).
  Blockly.Bruskey.functionNames_ = Object.create(null);

  if (!Blockly.Bruskey.variableDB_) {
    Blockly.Bruskey.variableDB_ =
        new Blockly.Names(Blockly.Bruskey.RESERVED_WORDS_);
  } else {
    Blockly.Bruskey.variableDB_.reset();
  }

  Blockly.Bruskey.variableDB_.setVariableMap(workspace.getVariableMap());

  var defvars = [];
  // Add developer variables (not created or named by the user).
  var devVarList = Blockly.Variables.allDeveloperVariables(workspace);
  for (var i = 0; i < devVarList.length; i++) {
    defvars.push(Blockly.Bruskey.variableDB_.getName(devVarList[i],
        Blockly.Names.DEVELOPER_VARIABLE_TYPE) + ' = None');
  }

  // Add user variables, but only ones that are being used.
  var variables = Blockly.Variables.allUsedVarModels(workspace);
  for (var i = 0; i < variables.length; i++) {
    defvars.push(Blockly.Bruskey.variableDB_.getName(variables[i].getId(),
        Blockly.Variables.NAME_TYPE) + ' = None');
  }

  Blockly.Bruskey.definitions_['variables'] = defvars.join('\n');
};

/**
 * Naked values are top-level blocks with outputs that aren't plugged into
 * anything.
 * @param {string} line Line of generated code.
 * @return {string} Legal line of code.
 */
Blockly.Bruskey.scrubNakedValue = function(line) {
  return line + '\n';
};

/**
 * Encode a string as a properly escaped Bruskey string, complete with quotes.
 * @param {string} string Text to encode.
 * @return {string} Python string.
 * @private
 */
Blockly.Bruskey.quote_ = function(string) {
  // Can't use goog.string.quote since % must also be escaped.
  string = string.replace(/\\/g, '\\\\')
                 .replace(/\n/g, '\\\n');

  // Follow the CPython behaviour of repr() for a non-byte string.
  var quote = '\'';
  if (string.indexOf('\'') !== -1) {
    if (string.indexOf('"') === -1) {
      quote = '"';
    } else {
      string = string.replace(/'/g, '\\\'');
    }
  };
  return quote + string + quote;
};

/**
 * Common tasks for generating Bruskey from blocks.
 * Handles comments for the specified block and any connected value blocks.
 * Calls any statements following this block.
 * @param {!Blockly.Block} block The current block.
 * @param {string} code The Bruskey code created for this block.
 * @param {boolean=} opt_thisOnly True to generate code for only this statement.
 * @return {string} Bruskey code with comments and subsequent blocks added.
 * @private
 */
Blockly.Bruskey.scrub_ = function(block, code, opt_thisOnly) {
  var commentCode = '';
  // Only collect comments for blocks that aren't inline.
  if (!block.outputConnection || !block.outputConnection.targetConnection) {
    // Collect comment for this block.
    var comment = block.getCommentText();
    comment = Blockly.utils.wrap(comment, Blockly.Bruskey.COMMENT_WRAP - 3);
    if (comment) {
      if (block.getProcedureDef) {
        // Use a comment block for function comments.
        commentCode += '"""' + comment + '\n"""\n';
      } else {
        commentCode += Blockly.Bruskey.prefixLines(comment + '\n', '// ');
      }
    }
    // Collect comments for all value arguments.
    // Don't collect comments for nested statements.
    for (var i = 0; i < block.inputList.length; i++) {
      if (block.inputList[i].type == Blockly.INPUT_VALUE) {
        var childBlock = block.inputList[i].connection.targetBlock();
        if (childBlock) {
          var comment = Blockly.Bruskey.allNestedComments(childBlock);
          if (comment) {
            commentCode += Blockly.Bruskey.prefixLines(comment, '// ');
          }
        }
      }
    }
  }
  var nextBlock = block.nextConnection && block.nextConnection.targetBlock();
  var nextCode = opt_thisOnly ? '' : Blockly.Bruskey.blockToCode(nextBlock);
  return commentCode + code + nextCode;
};

/**
 * Gets a property and adjusts the value, taking into account indexing, and
 * casts to an integer.
 * @param {!Blockly.Block} block The block.
 * @param {string} atId The property ID of the element to get.
 * @param {number=} opt_delta Value to add.
 * @param {boolean=} opt_negate Whether to negate the value.
 * @return {string|number}
 */
Blockly.Bruskey.getAdjustedInt = function(block, atId, opt_delta, opt_negate) {
  var delta = opt_delta || 0;
  if (block.workspace.options.oneBasedIndex) {
    delta--;
  }
  var defaultAtIndex = block.workspace.options.oneBasedIndex ? '1' : '0';
  var atOrder = delta ? Blockly.Bruskey.ORDER_ADDITIVE :
      Blockly.Bruskey.ORDER_NONE;
  var at = Blockly.Bruskey.valueToCode(block, atId, atOrder) || defaultAtIndex;

  if (Blockly.isNumber(at)) {
    // If the index is a naked number, adjust it right now.
    at = parseInt(at, 10) + delta;
    if (opt_negate) {
      at = -at;
    }
  } else {
    // If the index is dynamic, adjust it in code.
    if (delta > 0) {
      at = 'int(' + at + ' + ' + delta + ')';
    } else if (delta < 0) {
      at = 'int(' + at + ' - ' + -delta + ')';
    } else {
      at = 'int(' + at + ')';
    }
    if (opt_negate) {
      at = '-' + at;
    }
  }
  return at;
};

// LOGIC

Blockly.Bruskey['controls_if'] = function(block) {
  // If/elseif/else condition.
  var n = 0;
  var code = '', branchCode, conditionCode;
  do {
    conditionCode = Blockly.Bruskey.valueToCode(block, 'IF' + n,
      Blockly.Bruskey.ORDER_NONE) || 'false';
    branchCode = Blockly.Bruskey.statementToCode(block, 'DO' + n);
    code += (n == 0 ? 'if' : 'else if') + ' ' + conditionCode + ': \n' + branchCode + 'end';

    ++n;
  } while (block.getInput('IF' + n));

  if (block.getInput('ELSE')) {
    branchCode = Blockly.Bruskey.statementToCode(block, 'ELSE');
    code += ' else: \n' + branchCode + 'end';
  }
  return code + '\n';
};

Blockly.Bruskey['controls_ifelse'] = Blockly.Bruskey['controls_if'];

Blockly.Bruskey['logic_compare'] = function(block) {
  // Comparison operator.
  var OPERATORS = {
    'EQ': '==',
    'NEQ': '!=',
    'LT': '<',
    'LTE': '<=',
    'GT': '>',
    'GTE': '>='
  };
  var operator = OPERATORS[block.getFieldValue('OP')];
  var order = Blockly.Bruskey.ORDER_RELATIONAL;
  var argument0 = Blockly.Bruskey.valueToCode(block, 'A', order) || '0';
  var argument1 = Blockly.Bruskey.valueToCode(block, 'B', order) || '0';
  var code = argument0 + ' ' + operator + ' ' + argument1;
  return [code, order];
};

Blockly.Bruskey['logic_operation'] = function(block) {
  // Operations 'and', 'or'.
  var operator = (block.getFieldValue('OP') == 'AND') ? 'and' : 'or';
  var order = (operator == 'and') ? Blockly.Bruskey.ORDER_LOGICAL_AND :
      Blockly.Bruskey.ORDER_LOGICAL_OR;
  var argument0 = Blockly.Bruskey.valueToCode(block, 'A', order);
  var argument1 = Blockly.Bruskey.valueToCode(block, 'B', order);
  if (!argument0 && !argument1) {
    // If there are no arguments, then the return value is false.
    argument0 = 'False';
    argument1 = 'False';
  } else {
    // Single missing arguments have no effect on the return value.
    var defaultArgument = (operator == 'and') ? 'True' : 'False';
    if (!argument0) {
      argument0 = defaultArgument;
    }
    if (!argument1) {
      argument1 = defaultArgument;
    }
  }
  var code = argument0 + ' ' + operator + ' ' + argument1;
  return [code, order];
};

Blockly.Bruskey['logic_negate'] = function(block) {
  // Negation.
  var argument0 = Blockly.Bruskey.valueToCode(block, 'BOOL',
      Blockly.Bruskey.ORDER_LOGICAL_NOT) || 'True';
  var code = 'not ' + argument0;
  return [code, Blockly.Bruskey.ORDER_LOGICAL_NOT];
};

Blockly.Bruskey['logic_boolean'] = function(block) {
  // Boolean values true and false.
  var code = (block.getFieldValue('BOOL') == 'TRUE') ? 'True' : 'False';
  return [code, Blockly.Bruskey.ORDER_ATOMIC];
};

Blockly.Bruskey['logic_null'] = function(block) {
  // Null data type.
  return ['None', Blockly.Bruskey.ORDER_ATOMIC];
};

Blockly.Bruskey['logic_ternary'] = function(block) {
  // Ternary operator.
  var value_if = Blockly.Bruskey.valueToCode(block, 'IF',
      Blockly.Bruskey.ORDER_CONDITIONAL) || 'False';
  var value_then = Blockly.Bruskey.valueToCode(block, 'THEN',
      Blockly.Bruskey.ORDER_CONDITIONAL) || 'None';
  var value_else = Blockly.Bruskey.valueToCode(block, 'ELSE',
      Blockly.Bruskey.ORDER_CONDITIONAL) || 'None';
  var code = value_then + ' if ' + value_if + ' else ' + value_else;
  return [code, Blockly.Bruskey.ORDER_CONDITIONAL];
};

