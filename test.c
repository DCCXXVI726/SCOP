/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 17:59:30 by thorker           #+#    #+#             */
/*   Updated: 2020/02/10 00:13:17 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <GLFW/glfw3.h>
#include <stdio.h>

int main(void)
{
	if( !glfwInit() )
	{
		    fprintf( stderr, "Ошибка при инициализации GLFWn" );
			return -1;
	}
	GLFWwindow* window; // (В сопроводительном исходном коде эта переменная является глобальной)
	window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL);
	if( window == NULL ){
			fprintf( stderr, "Невозможно открыть окно GLFW. Если у вас Intel GPU, то он не поддерживает версию 3.3. Попробуйте версию уроков для OpenGL 2.1.n" );
				glfwTerminate();
				return -1;
	}
	glfwMakeContextCurrent(window);
	
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float f = 0.2f;
	//glViewport(0, 0, width, height);
	glClearColor(f, 0.3f, 0.3f, 1.0f);
	int i = 0;
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	do{
		i = 0;
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glPointSize(50);
		glBegin(GL_POINTS);
		glColor3f(1,1,1);
		glVertex2d(1,0);
		i++;
		glEnd();
		glfwSwapBuffers(window);
	} // Проверяем нажатие клавиши Escape или закрытие окна
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
			glfwWindowShouldClose(window) == 0 );
}
