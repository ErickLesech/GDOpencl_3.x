tool
extends VisualScriptCustomNode

#onready var data = preload("res://bin/gdnsproject.gdns").new()
# The name of the custom node as it appears in the search.
func _get_caption():
	return "OpenCL from file"

func _get_category():
	return "Input"

# The text displayed after the input port / sequence arrow.
func _get_text():
	return "val file"

func _get_input_value_port_count():
	return 3

# The types of the inputs per index starting from 0.
func _get_input_value_port_type(idx):
	
	match idx:
		0: return TYPE_INT
		1: return TYPE_INT
		2: return TYPE_REAL_ARRAY

func _get_output_value_port_count():
	return 1

# The types of outputs per index starting from 0.
func _get_output_value_port_type(idx):
	return TYPE_STRING

# The text displayed before each output node per index.
func _get_output_value_port_name(idx):
	return "log"
	
func _get_input_value_port_name(idx):
	match idx:
		0: return "fichier opencl"
		1: return "dimension"
		2: return "tableau"

func _has_input_sequence_port():
	return true
	
func _has_output_sequence_port():
	return true

# The number of output sequence ports to use
# (has to be at least one if you have an input sequence port).
func _get_output_sequence_port_count():
	return 1

func _step(inputs, outputs, start_mode, working_mem):
	

	var rng = RandomNumberGenerator.new()
	var numVal = inputs[0]
	
	var dim = inputs[1]
	var v = inputs[2]
	
	print(numVal)
	
	var data = preload("res://bin/gdnsproject.gdns").new()
	rng.randomize()
	
	data.setByFile(numVal,dim)
	data.writeMat(v,dim)
	data.runMat(dim)
	data.readMat(v,dim)

#	data.set(inputs[0],false,"matMult");
#	data.writeMat(v);
#	data.runMat();
#	data.readMat(v);
	
	if not data.errMsg.empty():
		print(data.errMsg)
	else:
		print("empty")
	
	print("log: ", data.log )
	print("content: ", data.getmsgStr());
	
	outputs[0] = data.log

	return 0
