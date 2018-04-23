#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <vector>
#include <queue>
#include <time.h>
#include <math.h>
#include <fstream>

#include "display.h"
#include "shader.h"
#include "terrainrenderer.h"
#include "renderer.h"
#include "masterrenderer.h"

#include "mesh.h"
#include "texturedmodel.h"
#include "entity.h"
#include "terrain.h"

#include "texture.h"
#include "simpleTexture.h"
#include "texturepack.h"

#include "transform.h"
#include "camera.h"
#include "input.h"
#include "sdl_backend.h"
#include "mytime.h"

#include "light.h"

#include "windows.h"

#include "entityloader.h"

#include "player.h"

//deklaracja danych
#include "defines/materials.h"
#include "defines/textures.h"
#include "defines/meshes.h"
#include "defines/texturedmodels.h"


// Converts degrees to radians.
#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)

// Converts radians to degrees.
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / M_PI)


//ToDo: ogarnij te zmienne globalne
bool m_mouseLocked;
glm::vec3 playerForward;
const glm::vec3 playerUp = glm::vec3(0.0f, 1.0f, 0.0f);
int camera_mode=0;
int camera_switch_cd=0;

class Atom 
{
public: 
	Atom(int mas, glm::vec3 vel, glm ::vec3 pos) {
		mass = mas;
		velocity = vel;
		momentum = glm::vec3(vel.x * mas, vel.y * mas, vel.z * mas);
		position = pos;
	}

	int mass;
	glm::vec3 velocity;
	glm::vec3 momentum;
	glm::vec3 position;
};


inline glm::vec3 vecXdouble(glm::vec3 a, double b) {
	return glm::vec3(a.x * b, a.y * b, a.z * b);
}
inline glm::vec3 vecXdouble(double a, glm::vec3 b) {
	return vecXdouble(b, a);
}

inline glm::vec3 vecXint(glm::vec3 a, int b) {
	return glm::vec3(a.x * b, a.y * b, a.z * b);
}
inline glm::vec3 vecXint(int a, glm::vec3 b) {
	return vecXdouble(b, a);
}

void genAtoms(int N, std::vector<Entity>& entites_scene_pos, std::vector<Entity>& entites_scene_mom, std::vector<Atom>& atoms) {
	for (int i = 0; i < N; i++) {
		float angle = rand() % 360;
		glm::vec3 v = Vec3Math::rot(glm::vec3(1.0f, 0.0f, 0.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f)); //moc kwaternionów;

		Entity New(TexturedModels::atom_model, glm::vec3((rand() % 600 - 300) / 10.0f, (rand() % 600) / 10.0f, 0.0f), 0, 0, 0, 1.0f);
		entites_scene_pos.push_back(New);
		atoms.push_back(Atom(30, v, New.GetPos()));
		entites_scene_mom.push_back(Entity(TexturedModels::atom_model, atoms.back().momentum, 0, 0, 0, 1.0f));
	}
}

void MOVE(Atom &atom, double l, double r, double t, double b) {
	atom.position += atom.velocity;//vecXdouble(atom.velocity, MyTime::getDelta());
	int i = 2;
	while (i--){
		//w jednej jednostce czasu odbicie moze zajsc o 2 scianki
		if (atom.position.x < l) {
			atom.position.x = l + abs(atom.position.x - l);
			atom.velocity.x = -atom.velocity.x;
		}
		else if (atom.position.x > r) {
			atom.position.x = r - abs(atom.position.x - r);
			atom.velocity.x = -atom.velocity.x;
		}
		else if (atom.position.y > t) {
			atom.position.y = t - abs(atom.position.y - t);
			atom.velocity.y = -atom.velocity.y;
		}
		else if (atom.position.y < b) {
			atom.position.y = b + abs(atom.position.y - b);
			atom.velocity.y = -atom.velocity.y;
		}
	}
	atom.momentum = vecXint(atom.mass, atom.velocity);
}

void defineState(int tab[11][11][5][5], Atom atom, double l, double b, double step_len_R, double step_len_P) {
	int Rx = modf((atom.position.x + abs(l)) , &step_len_R);
	int Ry = modf((atom.position.y + abs(b)), &step_len_R);
	int Px = modf((atom.momentum.x + abs(l)), &step_len_P);
	int Py = modf((atom.momentum.y + abs(b)), &step_len_P);

	tab[Rx][Ry][Px][Py]++;
}

void clearStates(int tab[11][11][5][5]) {
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			for (int k = 0; k < 5; k++) {
				for (int l = 0; l < 5; l++) {
					tab[i][j][k][l] = 0;
				}
			}
		}
	}
}

unsigned long long int productStates(int tab[11][11][5][5]) {
	unsigned long long int outcome = 1;
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 11; j++) {
			for (int k = 0; k < 5; k++) {
				for (int l = 0; l < 5; l++) {
					outcome *= (unsigned long long int) tab[i][j][k][l] ? tab[i][j][k][l] : 1;
				}
			}
		}
	}
	return outcome;
}

unsigned long long int factorial(int n)
{
	return (unsigned long long int)(n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}


long double count_thermodynamic_probability(int N, int states[11][11][5][5]) {
	long double outcome;
	outcome = (long double)factorial(N) / (long double)factorial(productStates(states));
	return outcome;
}

long double count_entrophy(long double x) {
	return logl(x);
}

void CreateRect(std::vector<Entity>& destination, glm::vec3 scale) {
	Entity w1(TexturedModels::quad_model, glm::vec3(0.0f, -30.0f, 0.0f), degreesToRadians(-90.0f), 0.0f, 0.0f, scale);		//BOTTOM
	Entity w2(TexturedModels::quad_model, glm::vec3(0.0f, 0.0f, -30.0f), 0.0f, 0.0f, 0.0f, scale);		//FAR
	Entity w3(TexturedModels::quad_model, glm::vec3(0.0f, 30.0f, 0.0f), degreesToRadians(90.0f), 0.0f, 0.0f, scale);		//TOP
	Entity w4(TexturedModels::quad_model, glm::vec3(30.0f, 0.0f, 0.0f), 0.0f, degreesToRadians(-90.0f), 0.0f, scale.x > scale.y ? scale.y : scale.x);		//RIGHt
	Entity w5(TexturedModels::quad_model, glm::vec3(-30.0f, 0.0f, 0.0f), 0.0f, degreesToRadians(90.0f), 0.0f, scale.x > scale.y ? scale.y : scale.x);		//LEFT
	Entity w6(TexturedModels::quad_model, glm::vec3(0.0f, 0.0f, 30.0f), 0.0f, degreesToRadians(-180.0f), 0.0f, scale);		//NEAR
	destination.push_back(w1);
	destination.push_back(w2);
	destination.push_back(w3);
	destination.push_back(w4);
	destination.push_back(w5);
	destination.push_back(w6);
}

void CreateGrid(std::vector<Entity>& destination, glm::vec3 scale, double from_x, double from_y, double len, int num) {
	double step = (double)len / (double)num;
	for (int i = 0; i <= num; i++) {
		Entity horizontal(TexturedModels::quad_black_model, glm::vec3(0.0f, from_y + i * step, 0.0f), 0.0f, degreesToRadians(180.0f), 0.0f, scale);		//BOTTOM
		Entity vertical(TexturedModels::quad_black_model, glm::vec3(from_x + i * step, 0.0f, 0.0f), 0.0f, degreesToRadians(180.0f), degreesToRadians(90.0f), scale);		//FAR
		destination.push_back(horizontal);
		destination.push_back(vertical);
	}
}


int main(int argc, char *argv[])
{
    AllocConsole();
    freopen("CONOUT$", "a", stdout);

    srand (time(NULL));

    std::cout<<"siema"<<std::endl;
    Display display(1200,900, "Hello World");

    Input input;

    Transform transform;

    Shader entityShader("./res/BasicShader");
    TerrainShader terrainShader("./res/TerrainShader");
    
    m_mouseLocked = false;

    Textures::Load();
    Meshes::Load();
    TexturedModels::Load();

    Camera camera(glm::vec3(0.0f, 0.0f, -80.0f), 70.0f, (float)display.GetWindowWidth()/(float)display.GetWindowHeight(), 1.0f, 2000.0f);
	
	camera.setPos(glm::vec3(0.0f, 0.0f, 30.0f));
	
	camera.setFocusPoint(&glm::vec3(0,30, -30));

	std::vector<Light> lights;
	//lights.push_back(Light(DIRECTIONAL_LIGHT, glm::vec3(0.0f), 1.0f, 0.0f, 0.0f, glm::vec3(0.8f), 0.6f, glm::vec3(1.0f, 0.0f, -1.0f)));
	lights.push_back(Light(POINT_LIGHT, glm::vec3(0.0f, 20.0f, -10.0f), 1.0f, 0.0f, 1.0f / 1000000.0f, glm::vec3(1.0f, 1.0f, 1.0f), 0.2f));
	//scene_position.push_back(Entity(TexturedModels::atom_model, lights[0].m_position, 0, 0, 0, 0.2));
    std::vector<Terrain> terrains;
    MasterRenderer masterRenderer(&entityShader, &terrainShader);

    int counter = 0;
    double time_counter = 0.0f;

    //initialize the time class
    MyTime::initialize();

//    GLuint *data;
    //GenerateObjects("world/objects.txt", terrain);


	////INITIALIZING ATOMS SIMULATION
	int N = 100;
	int states[11][11][5][5];

	double time_now = 0;

	std::fstream out;
	out.open("dane.txt", std::ios_base::out | std::ios_base::trunc);
	out.close();

	//std::queue<double>		times;
	//std::queue<long double> thermodynamic_probability;
	//std::queue<long double> entrophy;

	std::vector<Entity> scene_position;
	std::vector<Entity> scene_momentum;
	std::vector<Atom> atoms;
	genAtoms(N, scene_position, scene_momentum, atoms);

	CreateRect(scene_position, glm::vec3(30.0f,30.0f,1.0f));
	CreateGrid(scene_position, glm::vec3(30.0, 0.2f, 1.0f), -30.0f, -30.0f, 60.0f, 11);
	
	CreateRect(scene_momentum, glm::vec3(30.0f, 30.0f, 1.0f));
	CreateGrid(scene_momentum, glm::vec3(30.0, 0.2f, 1.0f), -30.0f, -30.0f, 60.0f, 5);

	////END OF INITIALIZING ATOMS SIMULATION



	int seconds = 0;
	while(!display.IsClosed())
    {
        MyTime::update();
        input.update();
		camera.Input();

		clearStates(states);

		int i = -1;
		for (auto atom : atoms) {
			MOVE(atoms[++i], -30.0f, 30.0f, 30.0f, -30.0f );
			scene_position[i].SetPos(atoms[i].position);
			scene_momentum[i].SetPos(atoms[i].momentum);
		
			defineState(states, atoms[i], -30.0f, -30.0f, 60.0f/11.0f, 60.0f/5.0f);
		}


		long double th_pb = count_thermodynamic_probability(N, states);
		//thermodynamic_probability.push(th_pb);
		long double en = count_entrophy(th_pb);

		out.open("dane.txt", std::ios_base::out | std::ios_base::app);
		out << time_now << "\t\t" << th_pb << "\n";
		out.close();

        if(SDLGetIsCloseRequested())
            display.Close();

        display.Clear(0.0f, 0.0f, 0.0f, 1.0f);

		if(camera.scene)
			masterRenderer.Render(scene_momentum, terrains, lights, camera);
		else 
			masterRenderer.Render(scene_position, terrains, lights, camera);
        display.Update();
        time_counter += MyTime::getDelta();
        counter ++;

        if (time_counter > 1.0f)
        {	
            std::cout<<"fps: "<<counter<<std::endl;
            counter=0;
            time_counter=0.0f;
        }

		time_now += MyTime::getDelta();
	}
    return 0;
}
