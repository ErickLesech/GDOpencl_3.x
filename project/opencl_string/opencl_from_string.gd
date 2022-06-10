tool
extends VisualScriptCustomNode

#onready var data = preload("res://bin/gdnsproject.gdns").new()
# The name of the custom node as it appears in the search.
func _get_caption():
	return "OpenCL from string"

func _get_category():
	return "Input"

# The text displayed after the input port / sequence arrow.
func _get_text():
	return "string"

func _get_input_value_port_count():
	return 4

# The types of the inputs per index starting from 0.
func _get_input_value_port_type(idx):
	if idx == 2:
		return TYPE_INT
	elif idx == 3:
		return TYPE_REAL_ARRAY
	return TYPE_STRING

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
		0: return "code opencl"
		1: return "nom de la fonction"
		2: return "dimension"
		3: return "tableau"
		
func _has_input_sequence_port():
	return true
	
func _has_output_sequence_port():
	return true

# The number of output sequence ports to use
# (has to be at least one if you have an input sequence port).
func _get_output_sequence_port_count():
	return 1

func _step(inputs, outputs, start_mode, working_mem):
	
	var tab = inputs[3]
	var rng = RandomNumberGenerator.new()
	var arg = inputs[0]
	var name_func = inputs[1]
	var dim = inputs[2]
	
	if name_func == "":
		print("manque nom de fonction")
		return -1;
	
	#var arg2 = inputs[0]
	var data = preload("res://bin/gdnsproject.gdns").new()
	rng.randomize()
	
	data.set(arg,false,name_func,dim)
	data.write(tab,dim)
	data.run(dim)
	data.read(tab,dim)

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
