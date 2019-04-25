/**
 * @fileoverview Generating Bruskey for logic blocks.
 */
'use strict';

goog.provide('Blockly.Bruskey.logic');

goog.require('Blockly.Bruskey');


Blockly.Bruskey['controls_if'] = function(block) {
  // If/elseif/else condition.
  var n = 0;
  var code = '', branchCode, conditionCode;
  do {
    conditionCode = Blockly.Bruskey.valueToCode(block, 'IF' + n,
      Blockly.Bruskey.ORDER_NONE) || 'false';
    branchCode = Blockly.Bruskey.statementToCode(block, 'DO' + n);
    code += (n == 0 ? 'if' : 'else if') + conditionCode + ': \n' + branchCode + 'end';

    ++n;
  } while (block.getInput('IF' + n));

  if (block.getInput('ELSE')) {
    branchCode = Blockly.Bruskey.statementToCode(block, 'ELSE');
    code += ' else: \n' + branchCode + 'end';
  }
  return code + '\n';
};

BlocklyBruskey['controls_ifelse'] = Blockly.Bruskey['controls_if'];

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
