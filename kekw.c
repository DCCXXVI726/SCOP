/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 21:37:54 by thorker           #+#    #+#             */
/*   Updated: 2020/02/10 03:50:21 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#include <SDL_image.h>
// Код шейдеров
const GLchar* vertexShaderSource = "#version 400 core\n"
	"layout (location = 0) in vec3 position;\n"
	"layout (location = 1) in vec3 color;\n"
	"layout (location = 2) in vec2 texCoord;\n"
	"uniform float alpha;\n"
	"out vec3 ourColor;\n"
	"out vec2 TexCoord;\n"
	"void main()\n"
	"{\n"
	"TexCoord = texCoord;\n"
	"gl_Position = vec4(sin(alpha + position.x), cos(alpha + position.y), position.z, 1.0);\n"
	"ourColor = vec3(color.x * sin(alpha), color.y * cos(alpha), color.z * sin(alpha));\n"
	"}\0";
const GLchar* fragmentShaderSource = "#version 400 core\n"
	"in vec3 ourColor;\n"
	"in vec2 TexCoord;\n"
	"out vec4 color;\n"
	"uniform sampler2D ourTexture;\n"
	"void main()\n"
	"{\n"
	"color = texture(ourTexture, TexCoord);\n"
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
	SDL_Surface *img = IMG_Load("cat.png");
	ft_putnbrln(img->h);
	ft_putnbrln(img->w);
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
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f
    };
	/*
	GLfloat texCoords[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		0.5f, 1.0f
	};
	*/
	//установка поведения текстуры за границами координатной плоскости
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	//Что-то связанное с минимаппингом
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//Загрузка текстур
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	unsigned char *emg2 = (unsigned char*) img->pixels;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->w, img->h, 0, GL_RGB, GL_UNSIGNED_BYTE, emg2);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( GLvoid * ) 0 );
    glEnableVertexAttribArray( 0 );
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( GLvoid * ) (3 * sizeof(GLfloat)));
	glEnableVertexAttribArray( 1 );
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( GLvoid * ) (6 * sizeof(GLfloat)));
	glEnableVertexAttribArray( 2 );
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
		glBindTexture(GL_TEXTURE_2D, texture);
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
