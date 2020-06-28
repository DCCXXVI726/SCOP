/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 21:37:54 by thorker           #+#    #+#             */
/*   Updated: 2020/06/28 19:14:38 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

//функция для закрытия если нажат escape можно заменить функцией в test.c
void	key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	(void)mode;
	(void)scancode;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int	main()
{

	//блок для создания окна
	GLFWwindow *window;
	int height;
	int width;

	//Инициализация GLFW (не забыть добавить проверку)
	glfwInit();
	//Задаем минимальную версию openGL "4.0"
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//Установка профайла для которого создается контекст (прогуглить эти функции)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//Выключение возможности изменения размера окна
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	//Создание окна
	if ((window = glfwCreateWindow(WINDOW_H, WINDOW_W, WINDOW_NAME, 0, 0)) == 0)
		exit(0);
	//перемещения окна в главый поток (обязательно)
	glfwMakeContextCurrent(window);
	//достаем значения высоты и ширины из экрана
	glfwGetFramebufferSize(window, &width, &height);
	//устанавливаем размеры для openGL (лучше это не использовать
	//первые два аргумента координаты левого нижней точки
	//вторые два правого верхнего
	//glViewport(0, 0, width, height);
	//регистрация функции для нажатие кнопки
	glfwSetKeyCallback(window, key_callback);
	//установка 
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	//Вершины
	GLfloat	vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};
	//Пишем вершинный шейдер
	const GLchar *vertexShaderSource = "#version 400 core\n"
		"layout (location = 0) in vec3 position;\n"
		"void main()\n"
		"{\n"
		"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
		"}\0";
	// Пишем фрагментный шейдер
	const GLchar *fragmentShaderSource = "#version 400 core\n"
		"out vec4 color;\n"
		"void main()\n"
		"{\n"
		"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\0";

	// Создаю переменну Vertex Buffer Objects  и создаю индификатор
	GLuint VBO;
	glGenBuffers(1, &VBO);
	//Привязка к нашему буферу
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Копирование вершин в буфер
	//Первый параметр тип буфера
	//Второй аргумент определяет количество данных в байтах
	//Третий сами данные
	//Четвертый аргмент это режим работы
	//GL_STATIC_DRAW: данные либо никогда не будут менятся либо будут изменятся очень редко
	//GL_DYNAMIC_DRAW: данные будут менятся довольно часто
	//GL_STREAM_DRAW: данные будут меняться при каждой отрисовке
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 0. Генерируем  VAO (Vertex Array Object)
	GLuint VAO;
	glGenVertexArraysAPPLE(1, &VAO);
    glBindVertexArrayAPPLE(VAO);
    // 2. Копируем наш массив вершин в буфер для OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. Устанавливаем указатели на вершинные атрибуты
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    //4. Отвязываем VAO
    glBindVertexArrayAPPLE(0);
	//создание объекта и сборка вершинного шейдера
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, 0);
	glCompileShader(vertexShader);

	//создание объекта и сборка фрагментного шейдера
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0);
	glCompileShader(fragmentShader);

	//Проверяем успешно ли собрался шейдер
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, 0, infoLog);
		ft_putendl("gg");
	}
	glGetShaderiv(fragmentShader , GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, 0, infoLog);
		ft_putendl("gg");
	}
	//создаем программу для шейдера
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	//присоединяем шейдеры к программе
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	
	//проверка шейдера
	glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, 0, infoLog);
		ft_putendl("gg");
	}
	//удалаем созданные шейдеры после связывание они больше не понадобяться.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//Пишем как чситывать вершины
	//Первый аргумент описывает какой аргумент шейдера мы хотим настроить.
	//Мы хотим специфицировать значение фргумента position, позиция которого была указана следующим образом
	//layout (location = 0)
	//Второй аргумент описывает размер аргумента в шейдере, у нас vec3 поэтому 3
	//Третий описывает размер используемый тип данных
	//Четвертый указывает необходимость нормализовать данные.
	//Пятый называется шагом и описывает расстояние между наборами данных.
	//Шестой смещение в начале буфера
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);	
	//игровой цикл
	//Проверяет должно ли окно быть закрыто
	while (!glfwWindowShouldClose(window))
	{
		//Проверка событий
		glfwPollEvents();
		//использует состояние цвета который определили в glClearColor
		glClear(GL_COLOR_BUFFER_BIT);
		//используем программу созданную выше
		glUseProgram(shaderProgram);
		glBindVertexArrayAPPLE(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArrayAPPLE(0);
		//Смена буферов(обновление окна)
		glfwSwapBuffers(window);
	}
	glDeleteVertexArraysAPPLE(1, &VAO);
	//очистка ресурсов
	glfwTerminate();
	return (0);
}
