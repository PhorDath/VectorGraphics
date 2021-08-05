#define OLC_PGE_APPLICATION
#include <olcPixelGameEngine.h>
#include <vector>
#include <cmath>

constexpr double pi = 3.14159265358979323846f;

using namespace std;

struct Point {
	float dX = 0.0f, dY = 0.0f;

	Point() {}
	Point(double x, double y) {
		dX = x;
		dY = y;
	}
};

struct Model {
	vector<Point> vPoints;

	Model() {}
	Model(vector<Point> p){
		vPoints = p;
	}
};

struct Object {
	Model* model;
	Model tModel;
	float x, y, scale = 1.0f, angle = 0.0f;

	Object() {}
	Object(Model* model, float x, float y, float scale, float angle) {
		this->model = model;
		this->tModel = *model;
		this->x = x;
		this->y = y;
		this->scale = scale;
		this->angle = angle;
	}
};


class VectorGraphic : public olc::PixelGameEngine {

public:
	VectorGraphic()
	{
		sAppName = "VectorGraphic";		
	}

private:
	vector<Model> vModels;
	vector<Object> vObjects;

	bool OnUserCreate() override
	{
		vModels.push_back(Model({ Point(1, 4), Point(3, 4), Point(2, 2) })); // add an isosceles triangle model in the application		
		Object O1(&vModels[0], ScreenWidth() / 2, ScreenHeight() / 2, 5, 90); // create an object with the triangle model and set its position in the middle of the screen
		vObjects.push_back(O1);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::WHITE); // clear screen


		// render objects
		for (Object O : vObjects) {
			// translate


			// scale
			for (int i = 0; i < vObjects[0].model->vPoints.size(); i++) {
				vObjects[0].tModel.vPoints[i].dX = vObjects[0].model->vPoints[i].dX * O.scale;// *fElapsedTime;
				vObjects[0].tModel.vPoints[i].dY = vObjects[0].model->vPoints[i].dY * O.scale;// *fElapsedTime;
			}

			// rotate
			for (int i = 0; i < vObjects[0].model->vPoints.size(); i++) {
				float angle = O.angle * pi / 180.0f;
				/*
				vObjects[0].tModel.vPoints[i].dX = vObjects[0].model->vPoints[i].dX * cos(angle) - vObjects[0].model->vPoints[i].dY * sin(angle);// * fElapsedTime;
				vObjects[0].tModel.vPoints[i].dY = vObjects[0].model->vPoints[i].dX * sin(angle) - vObjects[0].model->vPoints[i].dY * cos(angle);// * fElapsedTime;
				*/
			}

			// render triangle
			for (int i = 0; i < O.model->vPoints.size() - 1; i++) {
				for (int j = i; j < O.model->vPoints.size(); j++) {					
					DrawLine(O.tModel.vPoints[i].dX, O.tModel.vPoints[i].dY, O.tModel.vPoints[j].dX, O.tModel.vPoints[j].dY, olc::BLACK);
				}
			}
		}

		// handle user input
		if (GetKey(olc::Key::X).bHeld) {
			if (vObjects[0].scale < 100.0f) {
				vObjects[0].scale += 1.0f;
			}
		}
		if (GetKey(olc::Key::Z).bHeld) {
			if (vObjects[0].scale > 6.0f) {
				vObjects[0].scale -= 1.0f;
			}
			
		}
		if (GetKey(olc::Key::RIGHT).bPressed) {
			vObjects[0].angle += 15.0f;
		}
		if (GetKey(olc::Key::LEFT).bPressed) {
			vObjects[0].angle -= 15.0f;
		}

		return true;
	}
};

int main() {

	VectorGraphic demo;
	if (demo.Construct(256 * 4, 240 * 4, 1, 1, false, false))
		demo.Start();


	return 0;
}