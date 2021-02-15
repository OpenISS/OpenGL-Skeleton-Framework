# Comments
## Capitals
Inline comments should start with a capital letter:

```C++
GLFWwindow* setupGL()
{
    ...
    // Lock cursor to window
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    ...
}
```

## Docs
Use classic Doxygen/Javadoc syntax for comments outside of functions. This can be tedious to write and maintain. Use only where absolutely needed.

Note: One-liner Doxygen syntax (`///`) is preferred for simple stuff, ex:

```C++
/// Converts polar coordinates to cartesian
glm::vec3 getPosOnCircle(float degrees, float radius)
{
    ...
}
```

General syntax as described in https://developer.lsst.io/cpp/api-docs.html:

```C++
/**
 * A test class.
 * 
 * A more elaborate class description.
 */
class Doxygen_Test
{
public:

    /**
     * Supported coordinate systems for flux-conserving transformations.
     *
     * These values are used in arguments to various functions in this package.
     * Unless otherwise stated, these functions do not validate whether the data
     * set makes sense in the "from" coordinates.
     */
    enum class CoordType
    {
        /// Untransformed detector coordinates.
        PIXEL,
        /// Idealized detector coordinates after applying a distortion correction.
        WARP_PIXEL,
        /// Equatorial J2000.0 coordinates.
        SKY_WCS
    };

    /**
     * A constructor.
     * 
     * A more elaborate description of the constructor.
     */
    Doxygen_Test();

    /**
     * A destructor.
     * 
     * A more elaborate description of the destructor.
     */
    ~Doxygen_Test();

    /**
     * A function taking two arguments and returning an integer value.
     * 
     * @param a An integer argument.
     * @param s A constant character pointer.
     * @see Doxygen_Test()
     * @see ~Doxygen_Test()
     * @return The test results.
     */
    int testFirst(int a, const char* s);

    /**
     * Returns the cube transforms for a letter.
     * 
     * @param character Should be uppercase.
     * @return The cube transforms, or nullptr if the letter isn't supported.
     */
    const std::vector<glm::mat4>* getCubes(char character);

    double sum(std::vector<double>& const values);

    /// Must be clamped between 0 and 360
    float rotationDegrees;

    /**
     * Must be normalized.
     * 
     * Will behave erratically near the Z axis because of gimbal lock.
     */
    glm::vec3 rotationAxis;
};
```

## Over-commenting
Code is often self-explanatory, for example this comment would be unnecessary:

```C++
/// Returns sum of elements
double sum(std::vector<double>& const values);
```

Same for:
```C++
void setColor(glm::vec3& color)
{
    GLuint location = glGetUniformLocation(programID, "color");
    // Sets uniform
    glUniform3fv(location, 1, glm::value_ptr(color));
}
```

# Code
## Tabs vs spaces
Spaces.

## Case
`camelCase` for everything.

The functions in the `Module` class use `PascalCase` for emphasis but they're the only exceptions.

## `private` vs `protected`
`protected` is preferred over `private` because it's difficult to predict if a class will ever be extended or not. `protected` is more future-proof.

## Type qualifiers
Keep reference and pointer qualifiers glued to the type:

```C++
Node* localRoot;
Node& localRoot;
```

## Pointer vs reference
When defining a function that receives a memory location, a reference should be used instead if the location should logically never be null:

```C++
void addChild(Node& child)
{
    children.push_back(&child);
}
```

## Braces
Braces should open on a new line:

```C++
if (!success)
{
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    overallSuccess = false;
}
```

## Omitting braces in `if` statements
Braces should be skipped if all branches are one-liners:

```C++
if (key == GLFW_KEY_P)
    polygonMode = RenderMode::Point;
else if (key == GLFW_KEY_L)
    polygonMode = RenderMode::Line;
else
    polygonMode = RenderMode::Triangle;
```

However if most branches are not one-liners, then they should be kept for all branches for visual consistency.

## `switch` keyword
To avoid, generally.

## `NULL` vs `nullptr`
`nullptr`.

## Implicit & raw cast vs static_cast
Use `static_cast`. For example when converting an int to a float:

```C++
float f = static_cast<float>(i);
```

## `enum` vs `enum class`
Use `enum class` for its `::` scoped syntax:

```C++
enum class DrawMode
{
    INDEXED,
    VERTEX
};

DrawMode mode = DrawMode::INDEXED;
```

## Namespaces
The `using` keyword should be avoided for `std`. `std::` should be used explicitly for the standard library.

Same thing for `glm::`.

Other namespaces judged on a case-by-case basis.

# Misc
## Class member order
Member functions and properties should be declared in the following order:
* Constructor (if any)
* Destructor (if any)
* Public functions
* Public properties
* Protected functions
* Protected properties

In a `.cpp` file, implement functions in the same order that they were declared in the `.h` file.

## Blank line after access qualifiers
There should be a blank line after `public:` and `protected:`.

## `#pragma once`
There should be a `#pragma once` line at the top of each `.h` file.

## `.h` vs `.cpp` Files
For simplicity and readability, classes can be implemented entirely in `.h` files without accompanying `.cpp` files.

However if a circular `#include` arises, move one of the implementations entirely to a new `.cpp` file and [forward declare](https://stackoverflow.com/questions/4757565/what-are-forward-declarations-in-c).

## `#include` order
`#include` headers in the following order:
* If in a `.cpp` file, include its corresponding `.h` file followed by a blank space
* GLM or GLFW (sorted alphabetically)
* Standard library (sorted alphabetically)
* Our files (sorted alphabetically)

```C++
#include <glm/glm.hpp>
#include <vector>
#include "mesh.h"
#include "shader.h"
```

## End of file
There should be exactly 1 blank line at the end of each text file.

## Embedded text
For long strings such as shaders use the following syntax:

```C++
    const char* vertexSrc = R""""(
#version 330 core
...
void main()
{
    vertexColor = aColor;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * aPos;
}
)"""";
```

Align its indentation to the start of the line like above, otherwise the extra indentation would be included in the string.
