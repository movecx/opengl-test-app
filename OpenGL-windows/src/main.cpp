#include "definitions.h"

class GLDrawComponent {
public:

    virtual void draw( ) { }

protected:
    GLuint compile_shader( GLenum type, const char* source ) const {
        GLuint shader = glCreateShader( type );
        glShaderSource( shader, 1, &source, NULL );
        glCompileShader( shader );

        int success;
        glGetShaderiv( shader, GL_COMPILE_STATUS, &success );
        if ( !success ) {
            return 0;
        }

        return shader;
    }
};

class TriangleTest : public GLDrawComponent {

private:

    GLuint vertex_array{};
    GLuint vertex_buffer{};
    GLuint shader_program{};
    GLuint color_uniform{};
    color triangle_color{};

public:

    TriangleTest( color triangle_color ) : triangle_color(triangle_color) {

        constexpr vec3 vertices[ 3 ] = {
            { -0.5f, -0.5f, 0.0f },    // left
            { 0.5f, -0.5f, 0.0f },     // right
            { 0.0f,  0.5f, 0.0f }      // top
        };

        glGenVertexArrays( 1, &this->vertex_array );
        glBindVertexArray( this->vertex_array );

        glGenBuffers( 1, &this->vertex_buffer );
        glBindBuffer( GL_ARRAY_BUFFER, this->vertex_buffer );
        glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), ( void* )0 );
        glEnableVertexAttribArray( 0 );

        GLuint vertex_shader = this->compile_shader( GL_VERTEX_SHADER, vertex_shader_str );

        if ( !vertex_shader ) {
            std::cerr << "vertex shader failed to compile." << std::endl;
            exit( 1 );
        }

        GLuint fragment_shader = this->compile_shader( GL_FRAGMENT_SHADER, fragment_shader_str );

        if ( !fragment_shader ) {
            std::cerr << "fragment shader failed to compile." << std::endl;
            exit( 1 );
        }

        this->shader_program = glCreateProgram( );
        glAttachShader( this->shader_program, vertex_shader );
        glAttachShader( this->shader_program, fragment_shader );
        glLinkProgram( this->shader_program );

        auto success = 0;
        glGetProgramiv( this->shader_program, GL_LINK_STATUS, &success );
        if ( !success ) {
            std::cerr << "shader program link failed" << std::endl;
            exit( 1 );
        }

        this->color_uniform = glGetUniformLocation( this->shader_program, "triangle_color" );

        glDeleteShader( vertex_shader );
        glDeleteShader( fragment_shader );
    }

    ~TriangleTest( ) {
        glDeleteVertexArrays( 1, &vertex_array );
        glDeleteBuffers( 1, &vertex_buffer );
        glDeleteProgram( shader_program );
    }

    color get_color( ) {
        return this->triangle_color;
    }

    void set_color( color& new_color ) {
        this->triangle_color = new_color;
    }

    void draw( ) override {
        glUseProgram( this->shader_program );
        glUniform4fv( this->color_uniform, 1, this->triangle_color.to_gl() );
        glBindVertexArray( this->vertex_array );
        glDrawArrays( GL_TRIANGLES, 0, 3 );
    }
};

class GLRender {
private:

    GLFWwindow* window{};
    std::vector<std::shared_ptr<GLDrawComponent>> components{};
    color window_color{};

    static void framebuffer_callback( GLFWwindow* window, int width, int height ) {
        glViewport( 0, 0, width, height );
    }

    void process_input( GLFWwindow* window ) {
        if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
            glfwSetWindowShouldClose( window, true );
    }

public:

    GLRender( color window_color ) : window_color(window_color) {

        if ( !glfwInit( ) ) {
            std::cerr << "failed to initalze GLFW" << std::endl;
            exit( 1 );
        }

        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
        glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

        this->window = glfwCreateWindow( 800, 600, "OpenGL Test", nullptr, nullptr );
        if ( !this->window ) {
            std::cerr << "failed to initalze window" << std::endl;
            glfwTerminate( );
            exit( 1 );
        }

        glfwMakeContextCurrent( this->window );

        if ( glewInit( ) != GLEW_OK ) {
            std::cerr << "failed to initalze GLEW" << std::endl;
            exit( 1 );
        }

        glViewport( 0, 0, 800, 600 );
        glfwSetFramebufferSizeCallback( this->window, this->framebuffer_callback );

        glClearColor( this->window_color.red, this->window_color.green, this->window_color.blue, this->window_color.alpha );
    }

    ~GLRender( ) {
        glfwDestroyWindow( this->window );
        glfwTerminate( );
    }

    void add_component( std::shared_ptr<GLDrawComponent> component ) {
        this->components.push_back( component );
    }

    void draw_loop( ) {
        while ( !glfwWindowShouldClose( this->window ) ) {
            process_input( this->window );
            glClear( GL_COLOR_BUFFER_BIT );

            for ( auto& component : components ) {
                component->draw( );
            }

            glfwSwapBuffers( this->window );
            glfwPollEvents( );
        }
    }
};

int main() {

    auto renderer = std::make_shared<GLRender>( color( 255, 0, 255 ) );

    auto triangle_color = color{255, 0, 0, 0};

    auto triangle = std::make_shared<TriangleTest>( triangle_color );

    renderer->add_component( triangle );

    renderer->draw_loop( );

    return 0;
}