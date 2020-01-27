/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 21:37:54 by thorker           #+#    #+#             */
/*   Updated: 2020/01/27 06:26:51 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

// Код шейдеров
const GLchar* vertexShaderSource = "#version 400 core\n"
	"layout (location = 0) in vec3 position;\n"
	"layout (location = 1) in vec3 color;\n"
	"uniform float alpha;\n"
	"out vec3 ourColor;\n"
	"void main()\n"
	"{\n"
	"gl_Position = vec4(sin(alpha + position.x), cos(alpha + position.y), position.z, 1.0);\n"
	"ourColor = vec3(color.x * sin(alpha), color.y * cos(alpha), color.z * sin(alpha));\n"
	"}\0";
const GLchar* fragmentShaderSource = "#version 400 core\n"
	"in vec3 ourColor;\n"
	"out vec4 color;\n"
	"void main()\n"
	"{\n"
	"color = vec4(ourColor, 1.0f);\n"
	"}\n\0";

int main()
{
	//Инициализация
    glfwInit( );
    
    // Установка версии 4.0
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    // Устанавливает параметр для того, чтобы окно нельзя было изменять
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    // Создаю окно и проверяю
    GLFWwindow *window = glfwCreateWindow(WINDOW_W, WINDOW_H, WINDOW_NAME, 0, 0 );
	 if ( 0 == window )
    {
        glfwTerminate( );
	 	//выдать ошибку	
        return EXIT_FAILURE;
    }
    // получаю параметры окна
    int screenWidth, screenHeight;
    glfwGetFramebufferSize( window, &screenWidth, &screenHeight );
    // помещая окно в поток
    glfwMakeContextCurrent( window );
	// отрисовка линий вместо заполнения всего
   	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    //glewExperimental = GL_TRUE;
    // инициализация glew 
    if ( GLEW_OK != glewInit( ) )
    {
		//выдать ошибку
        ft_putendl("gg1");
        return EXIT_FAILURE;
    }
    
    // Define the viewport dimensions
    //glViewport( 0, 0, screenWidth, screenHeight );
    
    
    // Создаем шейдеры и компилируем их
    // Вершинный шейдер 
    GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( vertexShader, 1, &vertexShaderSource, NULL );
    glCompileShader( vertexShader );
    
    // Проверка скомпилироного шейдера
    GLint success;
    GLchar infoLog[512];
    
    glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success );
    if ( !success )
    {
        glGetShaderInfoLog( vertexShader, 512, NULL, infoLog );
        ft_putendl(infoLog);
		//выдать ошибку
    }
    
    // Фрагментный шейдер
    GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( fragmentShader, 1, &fragmentShaderSource, NULL );
    glCompileShader( fragmentShader );
    
    // Также проверяем
    glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success );
    
    if ( !success )
    {
        glGetShaderInfoLog( fragmentShader, 512, NULL, infoLog );
        ft_putendl(infoLog);
		// выдать ошибку
    }
    
    // Создаем программу и соединяем шейдеры
    GLuint shaderProgram = glCreateProgram( );
    glAttachShader( shaderProgram, vertexShader );
    glAttachShader( shaderProgram, fragmentShader );
    glLinkProgram( shaderProgram );
    
    // Проверка програмыы
    glGetProgramiv( shaderProgram, GL_LINK_STATUS, &success );
    
    if ( !success )
    {
        glGetProgramInfoLog( shaderProgram, 512, NULL, infoLog );
        ft_putendl(infoLog);
		//выдать ошибку
    }

    //удаление шейдеров
    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );
    
    
    // Координаты треугольника
    GLfloat vertices[] =
    {
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
	/*
	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};*/
    //создаем VBO и VAO buffer object и array object
    GLuint VBO, VAO;
    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );
	//glGenBuffers( 1, &EBO );
    // Привязываем VAO
    glBindVertexArray( VAO );
    // Копируем наш массив в буфер
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
	/*
	// Связываем EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    */
	// Устанавливаем указатели на вершине
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( GLfloat ), ( GLvoid * ) 0 );
    glEnableVertexAttribArray( 0 );
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( GLfloat ), ( GLvoid * ) (3 * sizeof(GLfloat)));
	glEnableVertexAttribArray( 1 );
    // отвязываем VBO
    glBindBuffer( GL_ARRAY_BUFFER, 0 ); 
	// Отвязываем VAO
    glBindVertexArray(0);
    // Игровой цикл
    while ( !glfwWindowShouldClose( window ) )
    {
        // Проверяем ивенты
        glfwPollEvents( );
        
        // устанавливаем цвет и можем перенести это наверх
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear(GL_COLOR_BUFFER_BIT);
        
        //отрисовка треугольника
		GLfloat timeValue = glfwGetTime();
		//GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
		// получаем адрес переменной uniform
		GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "alpha");
	   	//изменяем ее
	   	glUniform1f(vertexColorLocation, timeValue);	
        glUseProgram( shaderProgram );
		vertices[0] = sin(timeValue);
        glBindVertexArray( VAO );
        glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray( 0 );
        // Смена буферов
        glfwSwapBuffers( window );
    }
    
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays( 1, &VAO );
    glDeleteBuffers( 1, &VBO );
    
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate( );
    
    return EXIT_SUCCESS;
}


