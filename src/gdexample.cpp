#include "gdexample.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
using namespace godot;

void GDExample::_bind_methods() {

	ClassDB::bind_method(D_METHOD("get_amplitude"), &GDExample::get_amplitude);
	ClassDB::bind_method(D_METHOD("set_amplitude", "p_amplitude"), &GDExample::set_amplitude);
	ClassDB::add_property("GDExample", PropertyInfo(Variant::FLOAT, "amplitude"), "set_amplitude", "get_amplitude");

    ClassDB::bind_method(D_METHOD("get_speed"), &GDExample::get_speed);
	ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &GDExample::set_speed);
	ClassDB::add_property("GDExample", PropertyInfo(Variant::FLOAT, "speed", PROPERTY_HINT_RANGE, "0,20,0.01"), "set_speed", "get_speed");

	ADD_SIGNAL(MethodInfo("position_changed", PropertyInfo(Variant::OBJECT, "node"), PropertyInfo(Variant::VECTOR2, "new_pos")));
   
	ClassDB::bind_method(D_METHOD("OnSprite2DPositionChanged","node","new_pos"), &GDExample::OnSprite2DPositionChanged);

}

GDExample::GDExample() {
	// Initialize any variables here.
	time_passed = 0.0;
	time_emit   = 0.0;
	amplitude   = 10.0;
	speed       = 1.0;
}

GDExample::~GDExample() {
	// Add your cleanup here.
}

void GDExample::_ready()
{
	Node * sprite2DPlayers = get_node<Node>("/root/Main/Sprite2D");
	if(sprite2DPlayers!=nullptr)
	{
	 UtilityFunctions::print("parent_found: " + sprite2DPlayers->get_name());
	 sprite2DPlayers->connect("position_changed", Callable(this, "OnSprite2DPositionChanged"));
	}
}

void GDExample::_process(double delta) {
	time_passed += delta * speed;

	Vector2 new_position = Vector2(
		amplitude + (amplitude * sin(time_passed * 2.0)),
		amplitude + (amplitude * cos(time_passed * 1.5))
	);

	set_position(new_position);

	time_emit += delta;
	if (time_emit > 1.0) {
		emit_signal("position_changed", this, new_position);

		time_emit = 0.0;
	}
}

void GDExample::set_amplitude(const double p_amplitude) {
	amplitude = p_amplitude;
}

double GDExample::get_amplitude() const {
	return amplitude;
}

void GDExample::set_speed(const double p_speed) {
	speed = p_speed;
}

double GDExample::get_speed() const {
	return speed;
}

void GDExample::OnSprite2DPositionChanged(Object *node,Vector2 new_pos)
{
  UtilityFunctions::print(node->to_string(), " (",new_pos.x ,", " , new_pos.y,")");	
}
