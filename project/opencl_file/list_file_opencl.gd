tool
extends VisualScriptCustomNode

#onready var data = preload("res://bin/gdnsproject.gdns").new()
# The name of the custom node as it appears in the search.
func _get_caption():
	return "list file opencl"

func _get_category():
	return "Output"

# The text displayed after the input port / sequence arrow.
func _get_text():
	return "files"

func _get_input_value_port_count():
	return 0

# The types of the inputs per index starting from 0.
func _get_input_value_port_type(idx):
	return TYPE_STRING

func _get_output_value_port_count():
	return 2

# The types of outputs per index starting from 0.
func _get_output_value_port_type(idx):
	return TYPE_INT

# The text displayed before each output node per index.
func _get_output_value_port_name(idx):
	
	if idx == 0:
		return "FindMind.cl"
	if idx == 1:
		return "matMult.cl"

func _has_input_sequence_port():
	return true
	
func _has_output_sequence_port():
	return true

# The number of output sequence ports to use
# (has to be at least one if you have an input sequence port).
func _get_output_sequence_port_count():
	return 0

func _step(inputs, outputs, start_mode, working_mem):
	
	outputs[0] = 0
	outputs[1] = 1
	return 0
