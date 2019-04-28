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
Blockly.Bruskey.ORDER_ATOMIC = 0;           // 0 "" ...
Blockly.Bruskey.ORDER_NEW = 1.1;            // new
Blockly.Bruskey.ORDER_MEMBER = 1.2;         // . []
Blockly.Bruskey.ORDER_FUNCTION_CALL = 2;    // ()
Blockly.Bruskey.ORDER_INCREMENT = 3;        // ++
Blockly.Bruskey.ORDER_DECREMENT = 3;        // --
Blockly.Bruskey.ORDER_BITWISE_NOT = 4.1;    // ~
Blockly.Bruskey.ORDER_UNARY_PLUS = 4.2;     // +
Blockly.Bruskey.ORDER_UNARY_NEGATION = 4.3; // -
Blockly.Bruskey.ORDER_LOGICAL_NOT = 4.4;    // !
Blockly.Bruskey.ORDER_TYPEOF = 4.5;         // typeof
Blockly.Bruskey.ORDER_VOID = 4.6;           // void
Blockly.Bruskey.ORDER_DELETE = 4.7;         // delete
Blockly.Bruskey.ORDER_AWAIT = 4.8;          // await
Blockly.Bruskey.ORDER_EXPONENTIATION = 5.0; // **
Blockly.Bruskey.ORDER_MULTIPLICATION = 5.1; // *
Blockly.Bruskey.ORDER_DIVISION = 5.2;       // /
Blockly.Bruskey.ORDER_MODULUS = 5.3;        // %
Blockly.Bruskey.ORDER_SUBTRACTION = 6.1;    // -
Blockly.Bruskey.ORDER_ADDITION = 6.2;       // +
Blockly.Bruskey.ORDER_BITWISE_SHIFT = 7;    // << >> >>>
Blockly.Bruskey.ORDER_RELATIONAL = 8;       // < <= > >=
Blockly.Bruskey.ORDER_IN = 8;               // in
Blockly.Bruskey.ORDER_INSTANCEOF = 8;       // instanceof
Blockly.Bruskey.ORDER_EQUALITY = 9;         // == != === !==
Blockly.Bruskey.ORDER_BITWISE_AND = 10;     // &
Blockly.Bruskey.ORDER_BITWISE_XOR = 11;     // ^
Blockly.Bruskey.ORDER_BITWISE_OR = 12;      // |
Blockly.Bruskey.ORDER_LOGICAL_AND = 13;     // &&
Blockly.Bruskey.ORDER_LOGICAL_OR = 14;      // ||
Blockly.Bruskey.ORDER_CONDITIONAL = 15;     // ?:
Blockly.Bruskey.ORDER_ASSIGNMENT = 16;      // = += -= **= *= /= %= <<= >>= ...
Blockly.Bruskey.ORDER_YIELD = 17;         // yield
Blockly.Bruskey.ORDER_COMMA = 18;           // ,
Blockly.Bruskey.ORDER_NONE = 99;            // (...)

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
};

/**
 * Prepend the generated code with the variable definitions.
 * @param {string} code Generated code.
 * @return {string} Completed code.
 */
Blockly.Bruskey.finish = function(code) {
  // Convert the definitions dictionary into a list.
  var definitions = [];
  for (var name in Blockly.Bruskey.definitions_) {
    definitions.push(Blockly.Bruskey.definitions_[name]);
  }
  // Clean up temporary data.
  delete Blockly.Bruskey.definitions_;
  delete Blockly.Bruskey.functionNames_;
  Blockly.Bruskey.variableDB_.reset();
  return definitions.join('\n\n') + '\n\n\n' + code;
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
        commentCode += '\\\\ ' + comment + "\n";
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
      Blockly.Bruskey.ORDER_LOGICAL_NOT) || 'true';
  var code = 'not ' + argument0;
  return [code, Blockly.Bruskey.ORDER_LOGICAL_NOT];
};

Blockly.Bruskey['logic_boolean'] = function(block) {
  // Boolean values true and false.
  var code = (block.getFieldValue('BOOL') == 'TRUE') ? 'true' : 'false';
  return [code, Blockly.Bruskey.ORDER_ATOMIC];
};

Blockly.Bruskey['logic_null'] = function(block) {
  // Null data type.
  return ['None', Blockly.Bruskey.ORDER_ATOMIC];
};

Blockly.Bruskey['logic_ternary'] = function(block) {
  // Ternary operator.
  var value_if = Blockly.Bruskey.valueToCode(block, 'IF',
      Blockly.Bruskey.ORDER_CONDITIONAL) || 'false';
  var value_then = Blockly.Bruskey.valueToCode(block, 'THEN',
      Blockly.Bruskey.ORDER_CONDITIONAL) || 'none';
  var value_else = Blockly.Bruskey.valueToCode(block, 'ELSE',
      Blockly.Bruskey.ORDER_CONDITIONAL) || 'none';
  var code = value_then + ' if ' + value_if + ' else ' + value_else;
  return [code, Blockly.Bruskey.ORDER_CONDITIONAL];
};

// Built in functions

Blockly.Bruskey['initio_driveforward'] = function(block) {
  // Print statement.
  var msg = Blockly.Bruskey.valueToCode(block, 'DriveForward',
      Blockly.Bruskey.ORDER_NONE);
  return 'Robot.DriveForward(' + msg + ')\n';
};

Blockly.Bruskey['initio_drivebackward'] = function(block) {
  // Print statement.
  var msg = Blockly.Bruskey.valueToCode(block, 'DriveBackward',
      Blockly.Bruskey.ORDER_NONE);
  return 'Robot.DriveBackward(' + msg + ')\n';
};

Blockly.Bruskey['initio_spinright'] = function(block) {
  // Print statement.
  var msg = Blockly.Bruskey.valueToCode(block, 'SpinRight',
      Blockly.Bruskey.ORDER_NONE);
  return 'Robot.SpinRight(' + msg + ')\n';
};

Blockly.Bruskey['initio_spinleft'] = function(block) {
  // Print statement.
  var msg = Blockly.Bruskey.valueToCode(block, 'SpinLeft',
      Blockly.Bruskey.ORDER_NONE);
  return 'Robot.SpinLeft(' + msg + ')\n';
};

Blockly.Bruskey['initio_pause'] = function(block) {
  // Print statement.
  var msg = Blockly.Bruskey.valueToCode(block, 'Pause',
      Blockly.Bruskey.ORDER_NONE);
  return 'Robot.Pause(' + msg + ')\n';
};

Blockly.Bruskey['initio_leftlinedetected'] = function(block) {
  // Print statement.
  return 'Robot.Pause(' + msg + ')\n';
};

Blockly.Bruskey['initio_rightlinedetected'] = function(block) {
  // Print statement.
  return 'Robot.Pause(' + msg + ')\n';
};
Blockly.Bruskey['initio_getblobhalignment'] = function(block) {
  // Print statement.
  return 'Robot.Pause(' + msg + ')\n';
};
Blockly.Bruskey['initio_stop'] = function(block) {
  // Print statement.
  return 'Robot.Pause(' + msg + ')\n';
};
Blockly.Bruskey['initio_obstacledetected'] = function(block) {
  // Print statement.
  return 'Robot.Pause(' + msg + ')\n';
};
Blockly.Bruskey['initio_getdistance'] = function(block) {
  // Print statement.
  return 'Robot.Pause(' + msg + ')\n';
};
Blockly.Bruskey['initio_blobvisible'] = function(block) {
  // Print statement.
  return 'Robot.Pause(' + msg + ')\n';
};

// MATHS

Blockly.Bruskey['math_number'] = function(block) {
  // Numeric value.
  var code = parseFloat(block.getFieldValue('NUM'));
  var order = code >= 0 ? Blockly.Bruskey.ORDER_ATOMIC :
              Blockly.Bruskey.ORDER_UNARY_NEGATION;
  return [code, order];
};

Blockly.Bruskey['math_arithmetic'] = function(block) {
  // Basic arithmetic operators, and power.
  var OPERATORS = {
    'ADD': [' + ', Blockly.Bruskey.ORDER_ADDITION],
    'MINUS': [' - ', Blockly.Bruskey.ORDER_SUBTRACTION],
    'MULTIPLY': [' * ', Blockly.Bruskey.ORDER_MULTIPLICATION],
    'DIVIDE': [' / ', Blockly.Bruskey.ORDER_DIVISION],
    'POWER': [null, Blockly.Bruskey.ORDER_COMMA]  // Handle power separately.
  };
  var tuple = OPERATORS[block.getFieldValue('OP')];
  var operator = tuple[0];
  var order = tuple[1];
  var argument0 = Blockly.Bruskey.valueToCode(block, 'A', order) || '0';
  var argument1 = Blockly.Bruskey.valueToCode(block, 'B', order) || '0';
  var code;
  // Power in Bruskey requires a special case since it has no operator.
  if (!operator) {
    code = 'Math.pow(' + argument0 + ', ' + argument1 + ')';
    return [code, Blockly.Bruskey.ORDER_FUNCTION_CALL];
  }
  code = argument0 + operator + argument1;
  return [code, order];
};

Blockly.Bruskey['math_single'] = function(block) {
  // Math operators with single operand.
  var operator = block.getFieldValue('OP');
  var code;
  var arg;
  if (operator == 'NEG') {
    // Negation is a special case given its different operator precedence.
    arg = Blockly.Bruskey.valueToCode(block, 'NUM',
        Blockly.Bruskey.ORDER_UNARY_NEGATION) || '0';
    if (arg[0] == '-') {
      // --3 is not legal in JS.
      arg = ' ' + arg;
    }
    code = '-' + arg;
    return [code, Blockly.Bruskey.ORDER_UNARY_NEGATION];
  }
  if (operator == 'SIN' || operator == 'COS' || operator == 'TAN') {
    arg = Blockly.Bruskey.valueToCode(block, 'NUM',
        Blockly.Bruskey.ORDER_DIVISION) || '0';
  } else {
    arg = Blockly.Bruskey.valueToCode(block, 'NUM',
        Blockly.Bruskey.ORDER_NONE) || '0';
  }
  // First, handle cases which generate values that don't need parentheses
  // wrapping the code.
  switch (operator) {
    case 'ABS':
      code = 'Math.abs(' + arg + ')';
      break;
    case 'ROOT':
      code = 'Math.sqrt(' + arg + ')';
      break;
    case 'LN':
      code = 'Math.log(' + arg + ')';
      break;
    case 'EXP':
      code = 'Math.exp(' + arg + ')';
      break;
    case 'POW10':
      code = 'Math.pow(10,' + arg + ')';
      break;
    case 'ROUND':
      code = 'Math.round(' + arg + ')';
      break;
    case 'ROUNDUP':
      code = 'Math.ceil(' + arg + ')';
      break;
    case 'ROUNDDOWN':
      code = 'Math.floor(' + arg + ')';
      break;
    case 'SIN':
      code = 'Math.sin(' + arg + ' / 180 * Math.PI)';
      break;
    case 'COS':
      code = 'Math.cos(' + arg + ' / 180 * Math.PI)';
      break;
    case 'TAN':
      code = 'Math.tan(' + arg + ' / 180 * Math.PI)';
      break;
  }
  if (code) {
    return [code, Blockly.Bruskey.ORDER_FUNCTION_CALL];
  }
  // Second, handle cases which generate values that may need parentheses
  // wrapping the code.
  switch (operator) {
    case 'LOG10':
      code = 'Math.log(' + arg + ') / Math.log(10)';
      break;
    case 'ASIN':
      code = 'Math.asin(' + arg + ') / Math.PI * 180';
      break;
    case 'ACOS':
      code = 'Math.acos(' + arg + ') / Math.PI * 180';
      break;
    case 'ATAN':
      code = 'Math.atan(' + arg + ') / Math.PI * 180';
      break;
    default:
      throw Error('Unknown math operator: ' + operator);
  }
  return [code, Blockly.Bruskey.ORDER_DIVISION];
};

Blockly.Bruskey['math_constant'] = function(block) {
  // Constants: PI, E, the Golden Ratio, sqrt(2), 1/sqrt(2), INFINITY.
  var CONSTANTS = {
    'PI': ['Math.PI', Blockly.Bruskey.ORDER_MEMBER],
    'E': ['Math.E', Blockly.Bruskey.ORDER_MEMBER],
    'GOLDEN_RATIO':
        ['(1 + Math.sqrt(5)) / 2', Blockly.Bruskey.ORDER_DIVISION],
    'SQRT2': ['Math.SQRT2', Blockly.Bruskey.ORDER_MEMBER],
    'SQRT1_2': ['Math.SQRT1_2', Blockly.Bruskey.ORDER_MEMBER],
    'INFINITY': ['Infinity', Blockly.Bruskey.ORDER_ATOMIC]
  };
  return CONSTANTS[block.getFieldValue('CONSTANT')];
};

Blockly.Bruskey['math_number_property'] = function(block) {
  // Check if a number is even, odd, prime, whole, positive, or negative
  // or if it is divisible by certain number. Returns true or false.
  var number_to_check = Blockly.Bruskey.valueToCode(block, 'NUMBER_TO_CHECK',
      Blockly.Bruskey.ORDER_MODULUS) || '0';
  var dropdown_property = block.getFieldValue('PROPERTY');
  var code;
  if (dropdown_property == 'PRIME') {
    // Prime is a special case as it is not a one-liner test.
    var functionName = Blockly.Bruskey.provideFunction_(
        'mathIsPrime',
        ['function ' + Blockly.Bruskey.FUNCTION_NAME_PLACEHOLDER_ + '(n) {',
         '  // https://en.wikipedia.org/wiki/Primality_test#Naive_methods',
         '  if (n == 2 || n == 3) {',
         '    return true;',
         '  }',
         '  // False if n is NaN, negative, is 1, or not whole.',
         '  // And false if n is divisible by 2 or 3.',
         '  if (isNaN(n) || n <= 1 || n % 1 != 0 || n % 2 == 0 ||' +
            ' n % 3 == 0) {',
         '    return false;',
         '  }',
         '  // Check all the numbers of form 6k +/- 1, up to sqrt(n).',
         '  for (var x = 6; x <= Math.sqrt(n) + 1; x += 6) {',
         '    if (n % (x - 1) == 0 || n % (x + 1) == 0) {',
         '      return false;',
         '    }',
         '  }',
         '  return true;',
         '}']);
    code = functionName + '(' + number_to_check + ')';
    return [code, Blockly.Bruskey.ORDER_FUNCTION_CALL];
  }
  switch (dropdown_property) {
    case 'EVEN':
      code = number_to_check + ' % 2 == 0';
      break;
    case 'ODD':
      code = number_to_check + ' % 2 == 1';
      break;
    case 'WHOLE':
      code = number_to_check + ' % 1 == 0';
      break;
    case 'POSITIVE':
      code = number_to_check + ' > 0';
      break;
    case 'NEGATIVE':
      code = number_to_check + ' < 0';
      break;
    case 'DIVISIBLE_BY':
      var divisor = Blockly.Bruskey.valueToCode(block, 'DIVISOR',
          Blockly.Bruskey.ORDER_MODULUS) || '0';
      code = number_to_check + ' % ' + divisor + ' == 0';
      break;
  }
  return [code, Blockly.Bruskey.ORDER_EQUALITY];
};

Blockly.Bruskey['math_change'] = function(block) {
  // Add to a variable in place.
  var argument0 = Blockly.Bruskey.valueToCode(block, 'DELTA',
      Blockly.Bruskey.ORDER_ADDITION) || '0';
  var varName = Blockly.Bruskey.variableDB_.getName(
      block.getFieldValue('VAR'), Blockly.Variables.NAME_TYPE);
  return varName + ' = (typeof ' + varName + ' == \'number\' ? ' + varName +
      ' : 0) + ' + argument0 + ';\n';
};

// Rounding functions have a single operand.
Blockly.Bruskey['math_round'] = Blockly.Bruskey['math_single'];
// Trigonometry functions have a single operand.
Blockly.Bruskey['math_trig'] = Blockly.Bruskey['math_single'];

Blockly.Bruskey['math_on_list'] = function(block) {
  // Math functions for lists.
  var func = block.getFieldValue('OP');
  var list, code;
  switch (func) {
    case 'SUM':
      list = Blockly.Bruskey.valueToCode(block, 'LIST',
          Blockly.Bruskey.ORDER_MEMBER) || '[]';
      code = list + '.reduce(function(x, y) {return x + y;})';
      break;
    case 'MIN':
      list = Blockly.Bruskey.valueToCode(block, 'LIST',
          Blockly.Bruskey.ORDER_COMMA) || '[]';
      code = 'Math.min.apply(null, ' + list + ')';
      break;
    case 'MAX':
      list = Blockly.Bruskey.valueToCode(block, 'LIST',
          Blockly.Bruskey.ORDER_COMMA) || '[]';
      code = 'Math.max.apply(null, ' + list + ')';
      break;
    case 'AVERAGE':
      // mathMean([null,null,1,3]) == 2.0.
      var functionName = Blockly.Bruskey.provideFunction_(
          'mathMean',
          ['function ' + Blockly.Bruskey.FUNCTION_NAME_PLACEHOLDER_ +
              '(myList) {',
            '  return myList.reduce(function(x, y) {return x + y;}) / ' +
                  'myList.length;',
            '}']);
      list = Blockly.Bruskey.valueToCode(block, 'LIST',
          Blockly.Bruskey.ORDER_NONE) || '[]';
      code = functionName + '(' + list + ')';
      break;
    case 'MEDIAN':
      // mathMedian([null,null,1,3]) == 2.0.
      var functionName = Blockly.Bruskey.provideFunction_(
          'mathMedian',
          ['function ' + Blockly.Bruskey.FUNCTION_NAME_PLACEHOLDER_ +
              '(myList) {',
            '  var localList = myList.filter(function (x) ' +
              '{return typeof x == \'number\';});',
            '  if (!localList.length) return null;',
            '  localList.sort(function(a, b) {return b - a;});',
            '  if (localList.length % 2 == 0) {',
            '    return (localList[localList.length / 2 - 1] + ' +
              'localList[localList.length / 2]) / 2;',
            '  } else {',
            '    return localList[(localList.length - 1) / 2];',
            '  }',
            '}']);
      list = Blockly.Bruskey.valueToCode(block, 'LIST',
          Blockly.Bruskey.ORDER_NONE) || '[]';
      code = functionName + '(' + list + ')';
      break;
    case 'MODE':
      // As a list of numbers can contain more than one mode,
      // the returned result is provided as an array.
      // Mode of [3, 'x', 'x', 1, 1, 2, '3'] -> ['x', 1].
      var functionName = Blockly.Bruskey.provideFunction_(
          'mathModes',
          ['function ' + Blockly.Bruskey.FUNCTION_NAME_PLACEHOLDER_ +
              '(values) {',
            '  var modes = [];',
            '  var counts = [];',
            '  var maxCount = 0;',
            '  for (var i = 0; i < values.length; i++) {',
            '    var value = values[i];',
            '    var found = false;',
            '    var thisCount;',
            '    for (var j = 0; j < counts.length; j++) {',
            '      if (counts[j][0] === value) {',
            '        thisCount = ++counts[j][1];',
            '        found = true;',
            '        break;',
            '      }',
            '    }',
            '    if (!found) {',
            '      counts.push([value, 1]);',
            '      thisCount = 1;',
            '    }',
            '    maxCount = Math.max(thisCount, maxCount);',
            '  }',
            '  for (var j = 0; j < counts.length; j++) {',
            '    if (counts[j][1] == maxCount) {',
            '        modes.push(counts[j][0]);',
            '    }',
            '  }',
            '  return modes;',
            '}']);
      list = Blockly.Bruskey.valueToCode(block, 'LIST',
          Blockly.Bruskey.ORDER_NONE) || '[]';
      code = functionName + '(' + list + ')';
      break;
    case 'STD_DEV':
      var functionName = Blockly.Bruskey.provideFunction_(
          'mathStandardDeviation',
          ['function ' + Blockly.Bruskey.FUNCTION_NAME_PLACEHOLDER_ +
              '(numbers) {',
            '  var n = numbers.length;',
            '  if (!n) return null;',
            '  var mean = numbers.reduce(function(x, y) {return x + y;}) / n;',
            '  var variance = 0;',
            '  for (var j = 0; j < n; j++) {',
            '    variance += Math.pow(numbers[j] - mean, 2);',
            '  }',
            '  variance = variance / n;',
            '  return Math.sqrt(variance);',
            '}']);
      list = Blockly.Bruskey.valueToCode(block, 'LIST',
          Blockly.Bruskey.ORDER_NONE) || '[]';
      code = functionName + '(' + list + ')';
      break;
    case 'RANDOM':
      var functionName = Blockly.Bruskey.provideFunction_(
          'mathRandomList',
          ['function ' + Blockly.Bruskey.FUNCTION_NAME_PLACEHOLDER_ +
              '(list) {',
            '  var x = Math.floor(Math.random() * list.length);',
            '  return list[x];',
            '}']);
      list = Blockly.Bruskey.valueToCode(block, 'LIST',
          Blockly.Bruskey.ORDER_NONE) || '[]';
      code = functionName + '(' + list + ')';
      break;
    default:
      throw Error('Unknown operator: ' + func);
  }
  return [code, Blockly.Bruskey.ORDER_FUNCTION_CALL];
};

Blockly.Bruskey['math_modulo'] = function(block) {
  // Remainder computation.
  var argument0 = Blockly.Bruskey.valueToCode(block, 'DIVIDEND',
      Blockly.Bruskey.ORDER_MODULUS) || '0';
  var argument1 = Blockly.Bruskey.valueToCode(block, 'DIVISOR',
      Blockly.Bruskey.ORDER_MODULUS) || '0';
  var code = argument0 + ' % ' + argument1;
  return [code, Blockly.Bruskey.ORDER_MODULUS];
};

Blockly.Bruskey['math_constrain'] = function(block) {
  // Constrain a number between two limits.
  var argument0 = Blockly.Bruskey.valueToCode(block, 'VALUE',
      Blockly.Bruskey.ORDER_COMMA) || '0';
  var argument1 = Blockly.Bruskey.valueToCode(block, 'LOW',
      Blockly.Bruskey.ORDER_COMMA) || '0';
  var argument2 = Blockly.Bruskey.valueToCode(block, 'HIGH',
      Blockly.Bruskey.ORDER_COMMA) || 'Infinity';
  var code = 'Math.min(Math.max(' + argument0 + ', ' + argument1 + '), ' +
      argument2 + ')';
  return [code, Blockly.Bruskey.ORDER_FUNCTION_CALL];
};

Blockly.Bruskey['math_random_int'] = function(block) {
  // Random integer between [X] and [Y].
  var argument0 = Blockly.Bruskey.valueToCode(block, 'FROM',
      Blockly.Bruskey.ORDER_COMMA) || '0';
  var argument1 = Blockly.Bruskey.valueToCode(block, 'TO',
      Blockly.Bruskey.ORDER_COMMA) || '0';
  var functionName = Blockly.Bruskey.provideFunction_(
      'mathRandomInt',
      ['function ' + Blockly.Bruskey.FUNCTION_NAME_PLACEHOLDER_ +
          '(a, b) {',
       '  if (a > b) {',
       '    // Swap a and b to ensure a is smaller.',
       '    var c = a;',
       '    a = b;',
       '    b = c;',
       '  }',
       '  return Math.floor(Math.random() * (b - a + 1) + a);',
       '}']);
  var code = functionName + '(' + argument0 + ', ' + argument1 + ')';
  return [code, Blockly.Bruskey.ORDER_FUNCTION_CALL];
};

Blockly.Bruskey['math_random_float'] = function(block) {
  // Random fraction between 0 and 1.
  return ['Math.random()', Blockly.Bruskey.ORDER_FUNCTION_CALL];
};

Blockly.Bruskey['math_atan2'] = function(block) {
  // Arctangent of point (X, Y) in degrees from -180 to 180.
  var argument0 = Blockly.Bruskey.valueToCode(block, 'X',
      Blockly.Bruskey.ORDER_COMMA) || '0';
  var argument1 = Blockly.Bruskey.valueToCode(block, 'Y',
      Blockly.Bruskey.ORDER_COMMA) || '0';
  return ['Math.atan2(' + argument1 + ', ' + argument0 + ') / Math.PI * 180',
      Blockly.Bruskey.ORDER_DIVISION];
};

// VARIABLES

Blockly.Bruskey['variables_get'] = function(block) {
  // Variable getter.
  var code = Blockly.Bruskey.variableDB_.getName(block.getFieldValue('VAR'),
      Blockly.Variables.NAME_TYPE);
  return [code, Blockly.Bruskey.ORDER_ATOMIC];
};

Blockly.Bruskey['variables_set'] = function(block) {
  // Variable setter.
  var argument0 = Blockly.Bruskey.valueToCode(block, 'VALUE',
      Blockly.Bruskey.ORDER_ASSIGNMENT) || '0';
  var varName = Blockly.Bruskey.variableDB_.getName(
      block.getFieldValue('VAR'), Blockly.Variables.NAME_TYPE);
  return varName + ' = ' + argument0 + '\n';
};

Blockly.Bruskey['variables_get_dynamic'] = Blockly.Bruskey['variables_get'];
Blockly.Bruskey['variables_set_dynamic'] = Blockly.Bruskey['variables_set'];

// PROCEDURES

Blockly.Bruskey['procedures_defreturn'] = function(block) {
  // Define a procedure with a return value.
  var funcName = Blockly.Bruskey.variableDB_.getName(
      block.getFieldValue('NAME'), Blockly.Procedures.NAME_TYPE);
  var branch = Blockly.Bruskey.statementToCode(block, 'STACK');
  if (Blockly.Bruskey.STATEMENT_PREFIX) {
    var id = block.id.replace(/\$/g, '$$$$');  // Issue 251.
    branch = Blockly.Bruskey.prefixLines(
        Blockly.Bruskey.STATEMENT_PREFIX.replace(/%1/g,
        '\'' + id + '\''), Blockly.Bruskey.INDENT) + branch;
  }
  if (Blockly.Bruskey.INFINITE_LOOP_TRAP) {
    branch = Blockly.Bruskey.INFINITE_LOOP_TRAP.replace(/%1/g,
        '\'' + block.id + '\'') + branch;
  }
  var returnValue = Blockly.Bruskey.valueToCode(block, 'RETURN',
      Blockly.Bruskey.ORDER_NONE) || '';
  if (returnValue) {
    returnValue = Blockly.Bruskey.INDENT + 'return ' + returnValue + ';\n';
  }
  var args = [];
  for (var i = 0; i < block.arguments_.length; i++) {
    args[i] = Blockly.Bruskey.variableDB_.getName(block.arguments_[i],
        Blockly.Variables.NAME_TYPE);
  }
  var code = 'function ' + funcName + '(' + args.join(', ') + '): \n' +
      branch + returnValue + 'end';
  code = Blockly.Bruskey.scrub_(block, code);
  // Add % so as not to collide with helper functions in definitions list.
  Blockly.Bruskey.definitions_['%' + funcName] = code;
  return null;
};

// Defining a procedure without a return value uses the same generator as
// a procedure with a return value.
Blockly.Bruskey['procedures_defnoreturn'] =
    Blockly.Bruskey['procedures_defreturn'];

Blockly.Bruskey['procedures_callreturn'] = function(block) {
  // Call a procedure with a return value.
  var funcName = Blockly.Bruskey.variableDB_.getName(
      block.getFieldValue('NAME'), Blockly.Procedures.NAME_TYPE);
  var args = [];
  for (var i = 0; i < block.arguments_.length; i++) {
    args[i] = Blockly.Bruskey.valueToCode(block, 'ARG' + i,
        Blockly.Bruskey.ORDER_COMMA) || 'null';
  }
  var code = funcName + '(' + args.join(', ') + ')';
  return [code, Blockly.Bruskey.ORDER_FUNCTION_CALL];
};

Blockly.Bruskey['procedures_callnoreturn'] = function(block) {
  // Call a procedure with no return value.
  var funcName = Blockly.Bruskey.variableDB_.getName(
      block.getFieldValue('NAME'), Blockly.Procedures.NAME_TYPE);
  var args = [];
  for (var i = 0; i < block.arguments_.length; i++) {
    args[i] = Blockly.Bruskey.valueToCode(block, 'ARG' + i,
        Blockly.Bruskey.ORDER_COMMA) || 'null';
  }
  var code = funcName + '(' + args.join(', ') + ')\n';
  return code;
};

Blockly.Bruskey['procedures_ifreturn'] = function(block) {
  // Conditionally return value from a procedure.
  var condition = Blockly.Bruskey.valueToCode(block, 'CONDITION',
      Blockly.Bruskey.ORDER_NONE) || 'false';
  var code = 'if (' + condition + '):\n';
  if (block.hasReturnValue_) {
    var value = Blockly.Bruskey.valueToCode(block, 'VALUE',
        Blockly.Bruskey.ORDER_NONE) || 'null';
    code += Blockly.Bruskey.INDENT + 'return ' + value + ';\n';
  } else {
    code += Blockly.Bruskey.INDENT + 'return;\n';
  }
  code += 'end\n';
  return code;
};

// LOOPS

Blockly.Bruskey['controls_repeat_ext'] = function(block) {
  // Repeat n times.
  if (block.getField('TIMES')) {
    // Internal number.
    var repeats = String(Number(block.getFieldValue('TIMES')));
  } else {
    // External number.
    var repeats = Blockly.Bruskey.valueToCode(block, 'TIMES',
        Blockly.Bruskey.ORDER_ASSIGNMENT) || '0';
  }
  var branch = Blockly.Bruskey.statementToCode(block, 'DO');
  branch = Blockly.Bruskey.addLoopTrap(branch, block.id);
  var code = '';
  var loopVar = Blockly.Bruskey.variableDB_.getDistinctName(
      'count', Blockly.Variables.NAME_TYPE);
  var endVar = repeats;
  if (!repeats.match(/^\w+$/) && !Blockly.isNumber(repeats)) {
    var endVar = Blockly.Bruskey.variableDB_.getDistinctName(
        'repeat_end', Blockly.Variables.NAME_TYPE);
    code += 'var ' + endVar + ' = ' + repeats + ';\n';
  }
  code += 'for (var ' + loopVar + ' = 0; ' +
      loopVar + ' < ' + endVar + '; ' +
      loopVar + '++) {\n' +
      branch + '}\n';
  return code;
};

Blockly.Bruskey['controls_repeat'] =
    Blockly.Bruskey['controls_repeat_ext'];

Blockly.Bruskey['controls_whileUntil'] = function(block) {
  // Do while/until loop.
  var until = block.getFieldValue('MODE') == 'UNTIL';
  var argument0 = Blockly.Bruskey.valueToCode(block, 'BOOL',
      until ? Blockly.Bruskey.ORDER_LOGICAL_NOT :
      Blockly.Bruskey.ORDER_NONE) || 'false';
  var branch = Blockly.Bruskey.statementToCode(block, 'DO');
  branch = Blockly.Bruskey.addLoopTrap(branch, block.id);
  if (until) {
    argument0 = '!' + argument0;
  }
  return 'while ' + argument0 + ': \n' + branch + 'end\n';
};

Blockly.Bruskey['controls_for'] = function(block) {
  // For loop.
  var variable0 = Blockly.Bruskey.variableDB_.getName(
      block.getFieldValue('VAR'), Blockly.Variables.NAME_TYPE);
  var argument0 = Blockly.Bruskey.valueToCode(block, 'FROM',
      Blockly.Bruskey.ORDER_ASSIGNMENT) || '0';
  var argument1 = Blockly.Bruskey.valueToCode(block, 'TO',
      Blockly.Bruskey.ORDER_ASSIGNMENT) || '0';
  var increment = Blockly.Bruskey.valueToCode(block, 'BY',
      Blockly.Bruskey.ORDER_ASSIGNMENT) || '1';
  var branch = Blockly.Bruskey.statementToCode(block, 'DO');
  branch = Blockly.Bruskey.addLoopTrap(branch, block.id);
  var code;
  if (Blockly.isNumber(argument0) && Blockly.isNumber(argument1) &&
      Blockly.isNumber(increment)) {
    // All arguments are simple numbers.
    var up = parseFloat(argument0) <= parseFloat(argument1);
    code = 'for (' + variable0 + ' = ' + argument0 + '; ' +
        variable0 + (up ? ' <= ' : ' >= ') + argument1 + '; ' +
        variable0;
    var step = Math.abs(parseFloat(increment));
    if (step == 1) {
      code += up ? '++' : '--';
    } else {
      code += (up ? ' += ' : ' -= ') + step;
    }
    code += ') {\n' + branch + '}\n';
  } else {
    code = '';
    // Cache non-trivial values to variables to prevent repeated look-ups.
    var startVar = argument0;
    if (!argument0.match(/^\w+$/) && !Blockly.isNumber(argument0)) {
      startVar = Blockly.Bruskey.variableDB_.getDistinctName(
          variable0 + '_start', Blockly.Variables.NAME_TYPE);
      code += 'var ' + startVar + ' = ' + argument0 + ';\n';
    }
    var endVar = argument1;
    if (!argument1.match(/^\w+$/) && !Blockly.isNumber(argument1)) {
      var endVar = Blockly.Bruskey.variableDB_.getDistinctName(
          variable0 + '_end', Blockly.Variables.NAME_TYPE);
      code += 'var ' + endVar + ' = ' + argument1 + ';\n';
    }
    // Determine loop direction at start, in case one of the bounds
    // changes during loop execution.
    var incVar = Blockly.Bruskey.variableDB_.getDistinctName(
        variable0 + '_inc', Blockly.Variables.NAME_TYPE);
    code += 'var ' + incVar + ' = ';
    if (Blockly.isNumber(increment)) {
      code += Math.abs(increment) + ';\n';
    } else {
      code += 'Math.abs(' + increment + ');\n';
    }
    code += 'if (' + startVar + ' > ' + endVar + ') {\n';
    code += Blockly.Bruskey.INDENT + incVar + ' = -' + incVar + ';\n';
    code += '}\n';
    code += 'for (' + variable0 + ' = ' + startVar + '; ' +
        incVar + ' >= 0 ? ' +
        variable0 + ' <= ' + endVar + ' : ' +
        variable0 + ' >= ' + endVar + '; ' +
        variable0 + ' += ' + incVar + ') {\n' +
        branch + '}\n';
  }
  return code;
};