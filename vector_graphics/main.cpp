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
	float x, y;

	Object() {}
	Object(Model* m, float x, float y) {
		this->model = m;
		this->x = x;
		this->y = y;
	}
};


class VectorGraphic : public olc::PixelGameEngine {

public:
	VectorGraphic()
	{
		sAppName = "VectorGraphic";		
		vModels.push_back(Model({ Point(1, 4), Point(3, 4), Point(2, 2) }));
	}

private:
	vector<Model> vModels;

	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		Clear(olc::WHITE);

		for (Model m : vModels) {
			for (Point p1 : m.vPoints) {
				for (Point p2 : m.vPoints) {
					DrawLine(p1.dX, p1.dY, p2.dX, p2.dY, olc::BLACK);
				}				
			}
		}

		if (GetKey(olc::Key::X).bPressed) {
			double scale = 1.5f;
			for (Point &p : vModels.front().vPoints) {
				p.dX *= scale;
				p.dY *= scale;
			}
		}
		if (GetKey(olc::Key::Z).bPressed) {
			double scale = 0.5f;
			for (Point& p : vModels.front().vPoints) {
				p.dX *= scale;
				p.dY *= scale;
			}
		}

		if (GetKey(olc::Key::RIGHT).bPressed) {
			double angle = 15.0f * pi / 180.0f;
			for (Point& p : vModels.front().vPoints) {
				p.dX = p.dX * cos(angle) - p.dY * sin(angle);
				p.dY = p.dX * sin(angle) + p.dY * cos(angle);
			}
		}
		if (GetKey(olc::Key::LEFT).bPressed) {
			double angle = -15.0f * pi / 180.0f;
			for (Point& p : vModels.front().vPoints) {
				p.dX = p.dX * cos(angle) - p.dY * sin(angle);
				p.dY = p.dX * sin(angle) + p.dY * cos(angle);
			}
		}


		return true;
	}
};

int main() {

	VectorGraphic demo;
	if (demo.Construct(256 * 4, 240 * 4, 1, 1))
		demo.Start();


	return 0;
}