extends Spatial


# Declare member variables here. Examples:
# var a = 2
# var b = "text"

onready var data = preload("res://bin/gdnsproject.gdns").new()

var rng = RandomNumberGenerator.new()

# Called when the node enters the scene tree for the first time.
func _ready():
	
	var v = []
	
	rng.randomize()
	
	for i in range( 1 << 10 ):
		v.append(rng.randi_range(1,100))
	
	
	data.set()
	data.write(v)
	data.run()
	data.read(v)
	
	if not data.errMsg.empty():
		print(data.errMsg)
	else:
		print("empty")
		
	
	print("log: ", data.log )
	pass # Replace with function body.
