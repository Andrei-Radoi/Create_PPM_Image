//#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> 
#include <sstream> 
#include <iterator> 

using namespace std;

class Image
{
	int width = 0, height = 0;
	string name_I;

public:

	void set_resolution(int, int);
	void set_name(string);

	vector <int> create_I()
	{
		vector< int > vec_I{ 0 };
		int dim = width * height * 3;
		float a, b, d, e;

		a = 255 / (float)width;
		b = 255 / (float)height;

		vec_I.clear();

		for (int y = 1; y <= height; y++)
		{
			for (int x = 1; x <= width; x++)
			{

				d = a * (float)x;
				e = b * (float)y;

				int r = 255 - (int)e;             // gradient vertical: up - white, down - black
				int g = 255 - (int)d;             // gradient horizontal: left - white, right - black.
				int b = ((int)d * (int)e) / 255;  // blending mode (multiply ), between e & d.

				vec_I.push_back(r);
				vec_I.push_back(g);
				vec_I.push_back(b);
			}
		}
		return vec_I;
	}
	void writing_I();
	void open_I();
};

void Image::set_resolution(int k, int j)
{
	width = k;
	height = j;
}

void Image::set_name(string nn)
{
	name_I = nn;
}

void Image::writing_I()
{
	vector< int > vec_Img = create_I();
	ofstream img(name_I.c_str());
	string header_I = "P3 " + to_string(width) + " " + to_string(height) + " " + "255 ";
	ostringstream str_I;

	if (!vec_Img.empty())
	{
		copy(vec_Img.begin(), vec_Img.end(), ostream_iterator <int>(str_I, " "));
	}

	string img_Full = header_I + str_I.str();
	img << img_Full;
	img.close();
}

void Image::open_I()
{
	#if defined(_WIN32) || defined(__CYGWIN__)
		// Windows (x86 or x64)
		system(name_I.c_str());
	#elif defined(__linux__)
		// Linux
		// ...
	#elif defined(__APPLE__) && defined(__MACH__)
		// Mac OS
		string O_nume = "open " + nume_I;
		system(O_nume.c_str());
	#elif defined(unix) || defined(__unix__) || defined(__unix)
		// Unix like OS
		// ...
	#else
	#error Unknown environment!
	#endif
}

int main()
{
	Image img_1;
	img_1.set_resolution(1024, 1024);
	img_1.set_name("Image_1024.ppm");
	img_1.writing_I();
	img_1.open_I();

	return 0;
}
