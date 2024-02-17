using Godot;
using System;

public partial class Sprite2D : Godot.Sprite2D
{


  
    private double time_passed;

    private Vector2 start_position;
    private Vector2 new_position;
    [Export]
    public float amplitude = 10.0f;
    Sprite2D()
    {

        time_passed = 0.0f;
        start_position = default(Vector2);
        new_position = default(Vector2);

    }
    // Called when the node enters the scene tree for the first time.
    public override void _Ready()
    {

        GD.Print(String.Format("Sprite Ready time_passed={0:0,0}", time_passed));
        GD.Print(String.Format("Position = {0}:{1}", start_position.X, start_position.Y));
        start_position = Position;
        GD.Print(String.Format("Position = {0}:{1}", start_position.X, start_position.Y));
       
    }


    private void OnGDExamplePositionChanged(GodotObject node, Vector2 new_pos)
    {
        GD.Print(node.ToString() + " " + new_pos.ToString());
     
    }
    // Called every frame. 'delta' is the elapsed time since the previous frame.
    public override void _Process(double delta)
    {
        time_passed += delta;

        new_position.X = start_position.X + (float)(amplitude * Mathf.Sin(time_passed * 2.0));
        new_position.Y = start_position.Y + (float)(amplitude * Mathf.Cos(time_passed * 1.5));
        Position = new_position;

    }
}
