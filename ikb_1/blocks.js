Blockly.Blocks['ikb1_select_i2c_address'] = {
	init: function () {
		this.appendDummyInput()
			.appendField("Select I2C Address")
			.appendField(new Blockly.FieldDropdown([["0x48", "0x48"], ["0x49", "0x94"]]), "addr");
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour(180);
		this.setTooltip("");
		this.setHelpUrl("https://store.kidbright.info/plugin/7/iKB-1");
	}
};

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
	},
	xmlToolbox: function() {
		return `
		<block type="ikb1_digital_write">
		  	<value name="value">
				<shadow type="math_number">
					<field name="VALUE">1</field>
				</shadow>
			</value>
		</block>
		`;
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
	},
	xmlToolbox: function() {
		return `
		<block type="ikb1_motor">
		  	<value name="speed">
				<shadow type="math_number">
					<field name="VALUE">50</field>
				</shadow>
			</value>
		</block>
		`;
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
	},
	xmlToolbox: function() {
		return `
		<block type="ikb1_servo">
		  	<value name="angle">
				<shadow type="math_number">
					<field name="VALUE">90</field>
				</shadow>
			</value>
		</block>
		`;
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
	},
	xmlToolbox: function() {
		return `
		<block type="ikb1_servo2">
		  	<value name="speed">
				<shadow type="math_number">
					<field name="VALUE">50</field>
				</shadow>
			</value>
		</block>
		`;
	}
};

Blockly.Blocks['serial_header'] = {
	init: function () {

	},
	xmlToolbox: function() {
		// Create our shared stylesheet:
		const sheet = new CSSStyleSheet();
		sheet.replaceSync(`
		.HeaderLabelStyle > .blocklyFlyoutLabelText {
			font-size: 26px;
		}
		`);
		
		// Apply the stylesheet to a document:
		document.adoptedStyleSheets = [sheet];

		return `
		<sep gap="50"></sep>
		<label text="Serial" web-class="HeaderLabelStyle"></label>
		`;
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
	},
	xmlToolbox: function() {
		return `
		<block type="ikb1_serial_write">
		  	<value name="data">
				<shadow type="basic_string"></shadow>
			</value>
		</block>
		`;
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
	},
	xmlToolbox: function() {
		return `
		<block type="ikb1_serial_write_line">
		  	<value name="data">
				<shadow type="basic_string"></shadow>
			</value>
		</block>
		`;
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

Blockly.Blocks['ikb1_serial_read_one_byte'] = {
	init: function() {
		this.appendDummyInput()
			.appendField(Blockly.Msg.IKB_1.SERIAL_READ_ONE_BYTE);
		this.setInputsInline(true);
		this.setOutput(true, "Number");
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
	},
	xmlToolbox: function() {
		return `
		<block type="ikb1_serial_read">
		  	<value name="count">
				<shadow type="math_number">
					<field name="VALUE">1</field>
				</shadow>
			</value>
		</block>
		`;
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

Blockly.Blocks['robot_car_header'] = {
	init: function () {

	},
	xmlToolbox: function() {
		// Create our shared stylesheet:
		const sheet = new CSSStyleSheet();
		sheet.replaceSync(`
		.HeaderLabelStyle > .blocklyFlyoutLabelText {
			font-size: 26px;
		}
		`);
		
		// Apply the stylesheet to a document:
		document.adoptedStyleSheets = [sheet];

		return `
		<sep gap="50"></sep>
		<label text="Robot Car" web-class="HeaderLabelStyle"></label>
		`;
	}
};

var whellLogo = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAADwAAAA0CAQAAAB8ppOUAAAACXBIWXMAAA3XAAAN1wFCKJt4AAAFEWlUWHRYTUw6Y29tLmFkb2JlLnhtcAAAAAAAPD94cGFja2V0IGJlZ2luPSLvu78iIGlkPSJXNU0wTXBDZWhpSHpyZVN6TlRjemtjOWQiPz4gPHg6eG1wbWV0YSB4bWxuczp4PSJhZG9iZTpuczptZXRhLyIgeDp4bXB0az0iQWRvYmUgWE1QIENvcmUgNS42LWMxNDUgNzkuMTYzNDk5LCAyMDE4LzA4LzEzLTE2OjQwOjIyICAgICAgICAiPiA8cmRmOlJERiB4bWxuczpyZGY9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkvMDIvMjItcmRmLXN5bnRheC1ucyMiPiA8cmRmOkRlc2NyaXB0aW9uIHJkZjphYm91dD0iIiB4bWxuczp4bXA9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC8iIHhtbG5zOmRjPSJodHRwOi8vcHVybC5vcmcvZGMvZWxlbWVudHMvMS4xLyIgeG1sbnM6cGhvdG9zaG9wPSJodHRwOi8vbnMuYWRvYmUuY29tL3Bob3Rvc2hvcC8xLjAvIiB4bWxuczp4bXBNTT0iaHR0cDovL25zLmFkb2JlLmNvbS94YXAvMS4wL21tLyIgeG1sbnM6c3RFdnQ9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC9zVHlwZS9SZXNvdXJjZUV2ZW50IyIgeG1wOkNyZWF0b3JUb29sPSJBZG9iZSBQaG90b3Nob3AgQ0MgMjAxOSAoV2luZG93cykiIHhtcDpDcmVhdGVEYXRlPSIyMDE5LTAzLTA1VDE5OjE5KzA3OjAwIiB4bXA6TW9kaWZ5RGF0ZT0iMjAxOS0wMy0wNVQxOToyMDowNyswNzowMCIgeG1wOk1ldGFkYXRhRGF0ZT0iMjAxOS0wMy0wNVQxOToyMDowNyswNzowMCIgZGM6Zm9ybWF0PSJpbWFnZS9wbmciIHBob3Rvc2hvcDpDb2xvck1vZGU9IjEiIHBob3Rvc2hvcDpJQ0NQcm9maWxlPSJEb3QgR2FpbiAyMCUiIHhtcE1NOkluc3RhbmNlSUQ9InhtcC5paWQ6NGM0YjI5ODMtY2U2Ni1hMDRjLWI5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";

Blockly.Blocks['ikb1_motor_forward'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.IKB_1_MOTOR_FORWARD_MESSAGE,
			"args0": [{
				"type": "field_image",
				"src": whellLogo,
				"width": 18,
				"height": 16,
				"alt": "*",
				"flipRtl": false
			}, {
				"type": "input_value",
				"name": "speed",
				"check": "Number"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 180,
			"tooltip": Blockly.Msg.IKB_1_MOTOR_FORWARD_TOOLTIP,
			"helpUrl": "https://store.kidbright.info/plugin/7/iKB-1"
		});
	},
	xmlToolbox: function() {
		return `
		<block type="ikb1_motor_forward">
		  	<value name="speed">
				<shadow type="math_number">
					<field name="VALUE">50</field>
				</shadow>
			</value>
		</block>
		`;
	}
};

Blockly.Blocks['ikb1_motor_backward'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.IKB_1_MOTOR_BACKWARD_MESSAGE,
			"args0": [{
				"type": "field_image",
				"src": whellLogo,
				"width": 20,
				"height": 16,
				"alt": "*",
				"flipRtl": false
			}, {
				"type": "input_value",
				"name": "speed",
				"check": "Number"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 180,
			"tooltip": Blockly.Msg.IKB_1_MOTOR_BACKWARD_TOOLTIP,
			"helpUrl": "https://store.kidbright.info/plugin/7/iKB-1"
		});
	},
	xmlToolbox: function() {
		return `
		<block type="ikb1_motor_backward">
		  	<value name="speed">
				<shadow type="math_number">
					<field name="VALUE">50</field>
				</shadow>
			</value>
		</block>
		`;
	}
};

Blockly.Blocks['ikb1_motor_forward2'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.IKB_1_MOTOR_FORWARD_2_MESSAGE,
			"args0": [{
				"type": "field_image",
				"src": whellLogo,
				"width": 18,
				"height": 16,
				"alt": "*",
				"flipRtl": false
			}, {
				"type": "input_value",
				"name": "speed1",
				"check": "Number"
			}, {
				"type": "input_value",
				"name": "speed2",
				"check": "Number"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 180,
			"tooltip": Blockly.Msg.IKB_1_MOTOR_FORWARD_2_TOOLTIP,
			"helpUrl": "https://store.kidbright.info/plugin/7/iKB-1"
		});
	},
	xmlToolbox: function() {
		return `
		<block type="ikb1_motor_forward2">
		  	<value name="speed1">
				<shadow type="math_number">
					<field name="VALUE">50</field>
				</shadow>
			</value>
			<value name="speed2">
				<shadow type="math_number">
					<field name="VALUE">50</field>
				</shadow>
			</value>
		</block>
		`;
	}
};

Blockly.Blocks['ikb1_motor_backward2'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.IKB_1_MOTOR_BACKWARD_2_MESSAGE,
			"args0": [{
				"type": "field_image",
				"src": whellLogo,
				"width": 18,
				"height": 16,
				"alt": "*",
				"flipRtl": false
			}, {
				"type": "input_value",
				"name": "speed1",
				"check": "Number"
			}, {
				"type": "input_value",
				"name": "speed2",
				"check": "Number"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 180,
			"tooltip": Blockly.Msg.IKB_1_MOTOR_BACKWARD_2_TOOLTIP,
			"helpUrl": "https://store.kidbright.info/plugin/7/iKB-1"
		});
	},
	xmlToolbox: function() {
		return `
		<block type="ikb1_motor_backward2">
		  	<value name="speed1">
				<shadow type="math_number">
					<field name="VALUE">50</field>
				</shadow>
			</value>
			<value name="speed2">
				<shadow type="math_number">
					<field name="VALUE">50</field>
				</shadow>
			</value>
		</block>
		`;
	}
};

Blockly.Blocks['ikb1_motor_turn_left'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.IKB_1_MOTOR_TRUE_LEFT_MESSAGE,
			"args0": [{
				"type": "field_image",
				"src": whellLogo,
				"width": 18,
				"height": 16,
				"alt": "*",
				"flipRtl": false
			}, {
				"type": "input_value",
				"name": "speed",
				"check": "Number"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 180,
			"tooltip": Blockly.Msg.IKB_1_MOTOR_TRUE_LEFT_TOOLTIP,
			"helpUrl": "https://store.kidbright.info/plugin/7/iKB-1"
		});
	},
	xmlToolbox: function() {
		return `
		<block type="ikb1_motor_turn_left">
		  	<value name="speed">
				<shadow type="math_number">
					<field name="VALUE">50</field>
				</shadow>
			</value>
		</block>
		`;
	}
};

Blockly.Blocks['ikb1_motor_turn_right'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.IKB_1_MOTOR_TRUE_RIGHT_MESSAGE,
			"args0": [{
				"type": "field_image",
				"src": whellLogo,
				"width": 18,
				"height": 16,
				"alt": "*",
				"flipRtl": false
			}, {
				"type": "input_value",
				"name": "speed",
				"check": "Number"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 180,
			"tooltip": Blockly.Msg.IKB_1_MOTOR_TRUE_RIGHT_TOOLTIP,
			"helpUrl": "https://store.kidbright.info/plugin/7/iKB-1"
		});
	},
	xmlToolbox: function() {
		return `
		<block type="ikb1_motor_turn_right">
		  	<value name="speed">
				<shadow type="math_number">
					<field name="VALUE">50</field>
				</shadow>
			</value>
		</block>
		`;
	}
};

Blockly.Blocks['ikb1_motor_spin_left'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.IKB_1_MOTOR_SPIN_LEFT_MESSAGE,
			"args0": [{
				"type": "field_image",
				"src": whellLogo,
				"width": 18,
				"height": 16,
				"alt": "*",
				"flipRtl": false
			}, {
				"type": "input_value",
				"name": "speed",
				"check": "Number"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 180,
			"tooltip": Blockly.Msg.IKB_1_MOTOR_SPIN_LEFT_TOOLTIP,
			"helpUrl": "https://store.kidbright.info/plugin/7/iKB-1"
		});
	},
	xmlToolbox: function() {
		return `
		<block type="ikb1_motor_spin_left">
		  	<value name="speed">
				<shadow type="math_number">
					<field name="VALUE">50</field>
				</shadow>
			</value>
		</block>
		`;
	}
};

Blockly.Blocks['ikb1_motor_spin_right'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.IKB_1_MOTOR_SPEN_RIGHT_MESSAGE,
			"args0": [{
				"type": "field_image",
				"src": whellLogo,
				"width": 18,
				"height": 16,
				"alt": "*",
				"flipRtl": false
			}, {
				"type": "input_value",
				"name": "speed",
				"check": "Number"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 180,
			"tooltip": Blockly.Msg.IKB_1_MOTOR_SPEN_RIGHT_TOOLTIP,
			"helpUrl": "https://store.kidbright.info/plugin/7/iKB-1"
		});
	},
	xmlToolbox: function() {
		return `
		<block type="ikb1_motor_spin_right">
		  	<value name="speed">
				<shadow type="math_number">
					<field name="VALUE">50</field>
				</shadow>
			</value>
		</block>
		`;
	}
};

Blockly.Blocks['ikb1_motor_stop'] = {
	init: function() {
		this.jsonInit({
			"message0": Blockly.Msg.IKB_1_MOTOR_STOP_MESSAGE,
			"args0": [{
				"type": "field_image",
				"src": whellLogo,
				"width": 18,
				"height": 16,
				"alt": "*",
				"flipRtl": false
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 180,
			"tooltip": Blockly.Msg.IKB_1_MOTOR_STOP_TOOLTIP,
			"helpUrl": "https://store.kidbright.info/plugin/7/iKB-1"
		});
	}
};
