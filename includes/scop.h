/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 21:45:12 by thorker           #+#    #+#             */
/*   Updated: 2020/06/29 18:18:09 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

/*
** библиотека для редактирования окна и чтение действий пользователя
** openGL Frame Work
** GLEW для чтения функция opengl
*/

# define GLEW_STATIC
# include <fcntl.h>
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include "libft.h"
# include <math.h>
# include "scop_error.h"
# define VERSION	0.1.1
# define STEP		0.01f
# define WIN_H		600
# define WIN_W		800
# define WIN_NAME	"Scop"
# define FOV		60
# define NEAR		0.1f
# define FAR		1000.0f
# define MOUSE_SENX	0.0005f
# define MOUSE_SENY	0.0005f
/*
**	ERRORS
*/
# define MALLOC_E "problem with malloc"
# define GLFW_WIN_E "problem with glfw init"
# define GLFW_INIT_E "problem with glfw init"
# define GLEW_INIT_E "problem with glew init"
# define FRAG_E "problems with fragment shader"
# define VERT_E "problem with verxet shader"

typedef struct	s_obj
{
	GLfloat		*vertices;
	size_t		ver_size;
	GLuint		*indices;
	size_t		ind_size;
}				t_obj;

typedef struct	s_matrix
{
	GLfloat		*projection;
	GLfloat		*camera;
}				t_matrix;

typedef struct	s_camera
{
	GLfloat		x;
	GLfloat		y;
	GLfloat		z;
	GLfloat		phi;
	GLfloat		tetta;
	double		last_x;
	double		last_y;
}				t_camera;

typedef struct	s_vve
{
	GLuint		vbo;
	GLuint		vao;
	GLuint		ebo;
}				t_vve;

typedef struct	s_scop
{
	GLFWwindow	*window;
	GLuint		shader_program;
	t_vve		vve;
	t_camera	*camera;
	t_matrix	matrix;
}				t_scop;

void			ft_delete_object(t_obj **object);
t_vve			create_vao_vbo(void);
GLuint			create_program();
t_scop			*create_struct(void);
int				init_window(t_scop *scop);
void			ft_loop(t_scop *scop);
void			ft_clear(t_scop *scop);
void			ft_error(char *msg);
void			hooks(GLFWwindow *window, t_camera *camera);
void			update_matrix(t_matrix  matrix, t_camera *camera);
t_obj			*create_object(char *file_name);
int				add_vertices(char *line, t_obj *object);
int				add_indices(char *line, t_obj *object);
void			*ft_realloc(void *old_mem, size_t old_size, void *add_mem, size_t add_size);
char			*get_shader_code(char *name);
#endif
