##
## Raytracer, 2024
##
## Description:
## This project is a ray tracing program.
##
## Contributors:
## - Killian Cottrelle
## - Clement Barrier
## - Sonny Fourmont
##


# -------------------- G++ -------------------

CC		=	g++

CFLAGS	=	-std=c++20 -Wall -Wextra -Werror -I includes -g3 -Wno-unknown-pragmas

NAME	=	raytracer

SRC		=	Main.cpp \
			Scene.cpp	\
			Point3D.cpp \
			Vector3D.cpp \
			Ray.cpp	\
			Sphere.cpp \
			Plane.cpp \
			Rectangle3D.cpp	\
			Camera.cpp \
			Parser.cpp	\
			Objects.cpp	\
			Light.cpp	\

vpath %.cpp src
vpath %.cpp src/scene
vpath %.cpp src/scene/3D
vpath %.cpp src/scene/camera
vpath %.cpp src/scene/light
vpath %.cpp src/scene/objects
vpath %.cpp src/scene/ray
vpath %.cpp src/Parser

OBJS_DIR	=	objects

OBJS	=	$(patsubst %.cpp,$(OBJS_DIR)/%.o,$(SRC))

# ----------------- MakeFile -----------------

all:	create_dir $(NAME)

$(OBJS_DIR)/%.o : %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

create_dir :| $(OBJS_DIR)

$(OBJS_DIR):
	@mkdir -p $@

$(NAME):	$(OBJS)
	$(CC) -o $@ $^ -lconfig++

clean:
	rm -rf objects

fclean:	clean
	$(RM) $(NAME)

re : fclean all

.PHONY	:	all clean fclean re
