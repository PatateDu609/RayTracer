# Grammar

The scene file must end with a .rt extension. And must use the following grammar description.
This file will be used in order to specify the whole scene to the ray tracer engine.

The comments are used as in C: // for mono line comments and /* */ for multiple line comments.

**Warning**: The scene file is case sensitive.

## Scalar definition

A scene file can have multiple value types which are.

- ID which is a unique string that will define an object. It must be only composed by alphanumeric characters or
  underscores but can't begin by a number.
- Floating point numbers can be used to describe real quantities (as object sizes or light intensity).
- Integers are used to define quantities using only natural numbers (as the frame size in the resolution).
- Tuples are a group of scalars defined by a `()`.
- Objects are a group of scalars used as a struct in C, the property names in it are also IDs and must follow the ID
  definition. An object can be named using an ID.

Objects are defined by using the following syntax:

```
object_type [object_name_id] {
	property_name = value
	//...
}
```

## File organisation

The scene file will be organized in several blocks that will define each object in the world. It also describes metadata
objects that describe how the scene is organized (cameras, light...).

### Main block

The main block describes the scene as whole and can contain the following properties.

| Name       | Required | Description            | Value type                            | Default Value |
|------------|----------|------------------------|---------------------------------------|---------------|
| resolution | &check;  | Defines the frame size | **Tuple** of exactly two **Integers** | -             |

And the following block objects.

| Block Type    | Required | Description                                                      | Value type               |
|---------------|----------|------------------------------------------------------------------|--------------------------|
| point_light   | -        | A light object used in the ray tracing algorithm                 | Point Light **Object**   |
| ambient_light | &check;  | A global filter that behaves as the phong model ambient light    | Ambient Light **Object** |
| camera        | &check;  | Gives the actual point of view of the world                      | Camera **Object**        |
| sphere        | -        | Sets a sphere object using a sphere-ray intersection             | Sphere **Object**        |
| material      | -        | Creates a material that should be identified as explained above. | Material **Object**      |

### Point Light Block Object

| Property name | Required | Description                              | Value type                                  | Default Value   |
|---------------|----------|------------------------------------------|---------------------------------------------|-----------------|
| color         | -        | The actual color of the light            | **Tuple** of 3 integers between 0 and 255   | (255, 255, 255) |
| position      | &check;  | Sets the position of the light epicenter | **Tuple** of 3 real numbers                 | -               |
| intensity     | -        | Set the intensity of the light           | Real number, strictly in between of 0 and 1 | 1               |

### Ambient light Block Object

| Property name | Required | Description                    | Value type                                  | Default Value   |
|---------------|----------|--------------------------------|---------------------------------------------|-----------------|
| color         | -        | The actual color of the light  | **Tuple** of 3 integers between 0 and 255   | (255, 255, 255) |
| intensity     | -        | Set the intensity of the light | Real number, strictly in between of 0 and 1 | 1               |

### Camera Block Object

| Property name  | Required | Description                                                                       | Value type                  | Default Value |
|----------------|----------|-----------------------------------------------------------------------------------|-----------------------------|---------------|
| position       | &check;  | Sets the position of the camera point of view                                     | **Tuple** of 3 real numbers | -             |
| view_direction | &check;  | Sets the direction to which the camera is oriented                                | **Tuple** of 3 real numbers | -             |
| up_direction   | -        | Sets the direction of the up vector                                               | **Tuple** of 3 real numbers | (0, 1, 0)     |
| fov            | -        | Sets the angle of opening of the camera. This value must be specified in degrees. | Real numbers                | 90°           |

### Sphere Block Object

| Property name | Required | Description                              | Value type                                     | Default Value          |
|---------------|----------|------------------------------------------|------------------------------------------------|------------------------|
| position      | &check;  | Sets the position of the sphere's center | **Tuple** of 3 real numbers                    | -                      |
| material      | -        | Sets the material of the sphere          | Material object \| ID identifying the material | Diffuse white material |
| radius        | &check;  | Sets the sphere's radius                 | Real number                                    | -                      |

### Material Block Object

| Property name | Required | Description                                                             | Value type                                | Default Value |
|---------------|----------|-------------------------------------------------------------------------|-------------------------------------------|---------------|
| diffuse       | &check;  | Add a diffuse color to the material. The model used is the Phong model. | **Tuple** of 3 integers between 0 and 255 | -             |
