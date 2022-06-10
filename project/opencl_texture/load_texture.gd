extends Node

# Called when the node enters the scene tree for the first time.

onready var cube = get_node("../cube")

func _ready():
	
	var material = SpatialMaterial.new()
	var v = [10]
	var texture_brique = load("res://brique.jpeg") 
	var ocl = preload("res://bin/gdnsproject.gdns").new()

	if texture_brique == null:
		print("image does not load")
		return
		
	
	ocl.getBufferFromImage("res://brique.jpeg")
	
#	var taille = ocl.getTailleFile()
#	v = ocl.getDataImage();

#	for i in range(8):
#		print(v[i])

	ocl.toArrayTest(v)
	
	for i in range(10):
		print(v[i])
		
	material.albedo_texture = texture_brique
	
	$".".set_surface_material(0,material)
	


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
