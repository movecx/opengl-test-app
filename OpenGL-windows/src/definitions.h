#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>
#include <vector>

struct vec3 {
    float x, y, z;
};

struct color {
    union {
        float arr[ 4 ];
        struct {
            float red, green, blue, alpha;
        };
    };

    
    color( int red, int green, int blue, int alpha = 255 ) {
        from_rgb( red, green, blue, alpha );
    }


    color( float red, float green, float blue, float alpha = 1.0f ) {
        from_float( red, green, blue, alpha );
    }

 
    color( ) : red( 0.0f ), green( 0.0f ), blue( 0.0f ), alpha( 1.0f ) { }

    // initalize from RGB (0-255) to floating point.
    void from_rgb( int red, int green, int blue, int alpha ) {
        this->arr[ 0 ] = red / 255.f;
        this->arr[ 1 ] = green / 255.f;
        this->arr[ 2 ] = blue / 255.f;
        this->arr[ 3 ] = alpha / 255.f;
    }

    void from_float( float red, float green, float blue, float alpha ) {
        this->arr[ 0 ] = red;
        this->arr[ 1 ] = green;
        this->arr[ 2 ] = blue;
        this->arr[ 3 ] = alpha;
    }

    GLfloat* to_gl( ) {
        return this->arr;
    }
};

constexpr char* vertex_shader_str = R"(
    #version 330 core
    layout(location = 0) in vec3 xyz;
    void main()
    {
        gl_Position = vec4(xyz, 1.0);
    }
)";


constexpr char* fragment_shader_str = R"(
    #version 330 core
    out vec4 frag_color;
    uniform vec4 triangle_color;
    void main()
    {
        frag_color = triangle_color;
    }
)";