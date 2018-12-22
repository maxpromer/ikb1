Blockly.Blocks['ikb1_digital_read'] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.IKB_1.DIGTIAL_READ_PIN)
			.appendField(new Blockly.FieldDropdown([["0","0"], ["1","1"], ["2","2"], ["3","3"], ["4","4"], ["5","5"], ["6","6"], ["7","7"]]), "ch");
		this.setOutput(true, ["Number", "Boolean"]);
		this.setColour(180);
		this.setTooltip("");
		this.setHelpUrl("https://store.kidbright.info/plugin/7/iKB-1");
	}
};

Blockly.Blocks['ikb1_digital_write'] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.IKB_1.DIGTIAL_WRITE_PIN)
			.appendField(new Blockly.FieldDropdown([["0","0"], ["1","1"], ["2","2"], ["3","3"], ["4","4"], ["5","5"], ["6","6"], ["7","7"]]), "ch");
		this.appendValueInput("value")
			.setCheck(["Number", "Boolean"])
			.appendField(Blockly.Msg.IKB_1.TO);
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(180);
		this.setTooltip("");
		this.setHelpUrl("https://store.kidbright.info/plugin/7/iKB-1");
	}
};

Blockly.Blocks['ikb1_analog_read'] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.IKB_1.ANALOG_READ_PIN)
			.appendField(new Blockly.FieldDropdown([["0","0"], ["1","1"], ["2","2"], ["3","3"], ["4","4"], ["5","5"], ["6","6"], ["7","7"]]), "ch");
		this.setOutput(true, "Number");
		this.setColour(180);
		this.setTooltip("");
		this.setHelpUrl("https://store.kidbright.info/plugin/7/iKB-1");
	}
};

Blockly.Blocks['ikb1_motor'] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.IKB_1.SET_MOTOR)
			.appendField(new Blockly.FieldDropdown([["1","1"], ["2","2"], ["3","3"], ["4","4"]]), "ch")
			.appendField(Blockly.Msg.IKB_1.DIRECTION)
			.appendField(new Blockly.FieldDropdown([[Blockly.Msg.IKB_1.FORWARD,"1"], [Blockly.Msg.IKB_1.BACKWARD,"2"]]), "dir");
		this.appendValueInput("speed")
			.setCheck("Number")
			.appendField(Blockly.Msg.IKB_1.SPEED);
		this.appendDummyInput()
			.appendField("%");
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(180);
		this.setTooltip("");
		this.setHelpUrl("https://store.kidbright.info/plugin/7/iKB-1");
	}
};

Blockly.Blocks['ikb1_servo'] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.IKB_1.SET_SERVO)
			.appendField(new Blockly.FieldDropdown([["1","1"], ["2","2"], ["3","3"], ["4","4"], ["5","5"], ["6","6"]]), "ch");
		this.appendValueInput("angle")
			.setCheck("Number")
			.appendField(Blockly.Msg.IKB_1.DEGREE);
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(180);
		this.setTooltip("");
		this.setHelpUrl("https://store.kidbright.info/plugin/7/iKB-1");
	}
};

Blockly.Blocks['ikb1_servo2'] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.IKB_1.SET_SERVO2)
			.appendField(new Blockly.FieldDropdown([["1","1"], ["2","2"], ["3","3"], ["4","4"], ["5","5"], ["6","6"]]), "ch")
			.appendField(Blockly.Msg.IKB_1.DIRECTION)
			.appendField(new Blockly.FieldDropdown([[Blockly.Msg.IKB_1.FORWARD,"1"], [Blockly.Msg.IKB_1.BACKWARD,"2"]]), "dir");
		this.appendValueInput("speed")
			.setCheck("Number")
			.appendField(Blockly.Msg.IKB_1.SPEED);
		this.appendDummyInput()
			.appendField("%");
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(180);
		this.setTooltip("");
		this.setHelpUrl("https://store.kidbright.info/plugin/7/iKB-1");
	}
};

Blockly.Blocks['ikb1_serial_config'] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.IKB_1.SERIAL_SET_BAUD)
			.appendField(new Blockly.FieldDropdown([["9600","9600"], ["2400","2400"], ["57600","57600"], ["115200","115200"]]), "baud");
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(180);
		this.setTooltip("");
		this.setHelpUrl("https://store.kidbright.info/plugin/7/iKB-1");
	}
};

Blockly.Blocks['ikb1_serial_write'] = {
	init: function() {
		this.appendValueInput("data")
			.setCheck(["String", "Number", "Boolean"])
			.appendField(Blockly.Msg.IKB_1.SERIAL_WRITE);
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(180);
		this.setTooltip("");
		this.setHelpUrl("https://store.kidbright.info/plugin/7/iKB-1");
	}
};

Blockly.Blocks['ikb1_serial_write_line'] = {
	init: function() {
		this.appendValueInput("data")
			.setCheck(["String", "Number", "Boolean"])
			.appendField(Blockly.Msg.IKB_1.SERIAL_WRITE_NEW_LINE);
		this.setInputsInline(true);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(180);
		this.setTooltip("");
		this.setHelpUrl("https://store.kidbright.info/plugin/7/iKB-1");
	}
};

Blockly.Blocks['ikb1_serial_available'] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.IKB_1.SERIAL_AVAILABLE);
		this.setInputsInline(true);
		this.setOutput(true, ["Number", "Boolean"]);
		this.setColour(180);
		this.setTooltip("");
		this.setHelpUrl("https://store.kidbright.info/plugin/7/iKB-1");
	}
};

Blockly.Blocks['ikb1_serial_read'] = {
	init: function() {
		this.appendValueInput("count")
			.setCheck("Number")
			.appendField(Blockly.Msg.IKB_1.SERIAL_READ);
		this.appendDummyInput()
			.appendField(Blockly.Msg.IKB_1.BYTES);
		this.setInputsInline(true);
		this.setOutput(true, "String");
		this.setColour(180);
		this.setTooltip("");
		this.setHelpUrl("https://store.kidbright.info/plugin/7/iKB-1");
	}
};

Blockly.Blocks['ikb1_serial_read_string'] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.IKB_1.SERIAL_READ_STRING);
		this.setInputsInline(true);
		this.setOutput(true, "String");
		this.setColour(180);
		this.setTooltip("");
		this.setHelpUrl("https://store.kidbright.info/plugin/7/iKB-1");
	}
};

Blockly.Blocks['ikb1_serial_read_line'] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.IKB_1.SERIAL_READ_LINE);
		this.setInputsInline(true);
		this.setOutput(true, "String");
		this.setColour(180);
		this.setTooltip("");
		this.setHelpUrl("https://store.kidbright.info/plugin/7/iKB-1");
	}
};

Blockly.Blocks['ikb1_serial_read_until'] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.IKB_1.SERIAL_READ_UNTIL)
			.appendField(new Blockly.FieldTextInput("$"), "until");
		this.setInputsInline(true);
		this.setOutput(true, "String");
		this.setColour(180);
		this.setTooltip("");
		this.setHelpUrl("https://store.kidbright.info/plugin/7/iKB-1");
	}
}
