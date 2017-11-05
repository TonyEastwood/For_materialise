#include<stdint.h>
#include <fstream>
#include <iostream>
#include <math.h>
#include <conio.h>
#include <string>
#include <queue>
#pragma warning(disable:4996)
using namespace std;
const int MAX_QUANTITY_VERTEX = 10000;

class Vertex
{
private:
	//  static int Quantity_vertex=0;              //quantity vertex at now
	int Count_retaled_vertex = 0;                 //quantity of related vertex at now
	int index = 0;
	float x, y, z;
	int Related_vertex[1000];                     // the index of vertex which related with current vert
	float Distance_Related_vertex[1000];         // the index of vertex which related with current vert
public:
	Vertex() :x(0), y(0), z(0){};
	~Vertex(){};
	Vertex(float v_x, float v_y, float v_z, int *Quantity_vertex) : x(v_x), y(v_y), z(v_z)
	{
		index = *Quantity_vertex;
		*Quantity_vertex = *Quantity_vertex + 1;
	}
	inline void Initialization(float, float, float, int*);        //initialization vertex
	bool VertexVerify(float, float, float);
	friend float Distance(Vertex&, Vertex&);
	friend bool Add_Related_Vertex(Vertex&, Vertex&);       //add vertex as related
	inline float Get_x(){ return x; }
	inline float Get_y(){ return y; }
	inline float Get_z(){ return z; }
	inline int Get_count_related_vertex(){ return Count_retaled_vertex; }
	inline float Get_Index(){ return index; }                 //return index current Vertex
	inline int Get_Related_Vertex(int);                     //return index of related vertex
	inline float Get_Related_Distance(int);                 //return distance to related vertex

};

float Vertex::Get_Related_Distance(int i_ex)
{
	if (i_ex <= this->Get_count_related_vertex() && i_ex >= 0)
		return this->Distance_Related_vertex[i_ex];
	else return -1;

}
int Vertex::Get_Related_Vertex(int i_ex)
{
	if (i_ex <= this->Get_count_related_vertex() && i_ex >= 0)
		return this->Related_vertex[i_ex];
	else return -1;
}
bool Vertex::VertexVerify(float v_x, float v_y, float v_z)      //check if the vertex the same with current
{
	if (x == v_x && y == v_y && z == v_z)
		return true;
	else return false;

}
float Distance(Vertex& Vertex_1, Vertex& Vertex_2)             //return distance between two vertex
{
	return sqrt(pow((Vertex_1.Get_x() - Vertex_2.Get_x()), 2) + pow((Vertex_1.Get_y() - Vertex_2.Get_y()), 2) + pow((Vertex_1.Get_z() - Vertex_2.Get_z()), 2));

}
void Vertex::Initialization(float v_x, float v_y, float v_z, int *Quantity_vertex)    //initialization vertex
{
	x = v_x;
	y = v_y;
	z = v_z;
	index = *Quantity_vertex;
	*Quantity_vertex = *Quantity_vertex + 1;
}
bool Add_Related_Vertex(Vertex& Vertex_1, Vertex& Vertex_2)    //if Vertex 2 not exist in vertex1 then add to Vertex1 and Vertex2 appropriate index
{
	for (int i = 0; i<Vertex_1.Count_retaled_vertex; i++)
		if (Vertex_1.Related_vertex[i] == Vertex_2.Get_Index())
			return false;
	Vertex_1.Related_vertex[Vertex_1.Get_count_related_vertex()] = Vertex_2.Get_Index();
	Vertex_1.Distance_Related_vertex[Vertex_1.Get_count_related_vertex()] = Distance(Vertex_1, Vertex_2);

	Vertex_1.Count_retaled_vertex++;
	Vertex_2.Related_vertex[Vertex_2.Get_count_related_vertex()] = Vertex_1.Get_Index();
	Vertex_2.Distance_Related_vertex[Vertex_2.Get_count_related_vertex()] = Distance(Vertex_1, Vertex_2);
	Vertex_2.Count_retaled_vertex++;
	return true;
}

Vertex Massive_Vertex[MAX_QUANTITY_VERTEX];

bool InitializationFileStl(string FileName, int *Quantity_vertex)         //File initialization
{
	FILE *file_stl;
	uint8_t *buffer = new uint8_t[80];
	uint32_t temp_32;
	uint16_t temp_16;
	float *Coord_vertex = new float[12];
	if (file_stl = fopen(FileName.c_str(), "rb"))
	{

		fread(buffer, sizeof(uint8_t) * 80, 1, file_stl);
		fread(&temp_32, sizeof(uint32_t), 1, file_stl);
		cout << "The file was successfully opened! \n Quantity triangles in your model:";
		cout << temp_32 << endl;
		bool verify = false; // check if the vertex exist true - same false - diffrenet
		int Temp_Vertex_Index[3]; // index existens vertex
		for (int i = 0; i<temp_32; i++)
		{

			fread(Coord_vertex, sizeof(float) * 12, 1, file_stl);
			//  cout<<"NORMAL VECTOR:"<<endl;
			// cout<<Coord_vertex[0]<<" "<<Coord_vertex[1]<<" "<<Coord_vertex[2]<<endl;
			// cout<<"1 VERTEX:"<<endl;
			// cout<<Coord_vertex[3]<<" "<<Coord_vertex[4]<<" "<<Coord_vertex[5]<<endl;
			for (int k = 0; k<*Quantity_vertex; k++)
			{
				if (verify = Massive_Vertex[k].VertexVerify(Coord_vertex[3], Coord_vertex[4], Coord_vertex[5]))
				{
					Temp_Vertex_Index[0] = k;
					break;
				}
			}
			if (!verify)         //if vertex different then add vertex
			{
				if (*Quantity_vertex == MAX_QUANTITY_VERTEX - 1)
				{
					cout << "So much Vertex in your model, try to optimize it or choose another model" << endl;
					return false;
				}
				Massive_Vertex[*Quantity_vertex].Initialization(Coord_vertex[3], Coord_vertex[4], Coord_vertex[5], Quantity_vertex);
				Temp_Vertex_Index[0] = *Quantity_vertex - 1;
			}
			verify = false;

			//cout<<"2 VERTEX:"<<endl;
			// cout<<Coord_vertex[6]<<" "<<Coord_vertex[7]<<" "<<Coord_vertex[8]<<endl;
			for (int k = 0; k<*Quantity_vertex; k++)
			{
				if (verify = Massive_Vertex[k].VertexVerify(Coord_vertex[6], Coord_vertex[7], Coord_vertex[8]))
				{
					Temp_Vertex_Index[1] = k;
					break;
				}
			}
			if (!verify)      //if vertex different then add vertex
			{
				if (*Quantity_vertex == MAX_QUANTITY_VERTEX - 1)
				{
					cout << "So much Vertex in your model, try to optimize it or choose another model" << endl;
					return false;
				}
				Massive_Vertex[*Quantity_vertex].Initialization(Coord_vertex[6], Coord_vertex[7], Coord_vertex[8], Quantity_vertex);
				Temp_Vertex_Index[1] = *Quantity_vertex - 1;
			}
			verify = false;





			//cout<<"3 VERTEX:"<<endl;
			// cout<<Coord_vertex[9]<<" "<<Coord_vertex[10]<<" "<<Coord_vertex[11]<<endl;

			for (int k = 0; k<*Quantity_vertex; k++)
			{
				if (verify = Massive_Vertex[k].VertexVerify(Coord_vertex[9], Coord_vertex[10], Coord_vertex[11]))
				{
					Temp_Vertex_Index[2] = k;
					break;
				}
			}
			if (!verify)       //if vertex different then add vertex
			{
				if (*Quantity_vertex == MAX_QUANTITY_VERTEX - 1)
				{
					cout << "So much Vertex in your model, try to optimize it or choose another model" << endl;
					return false;
				}
				Massive_Vertex[*Quantity_vertex].Initialization(Coord_vertex[9], Coord_vertex[10], Coord_vertex[11], Quantity_vertex);
				Temp_Vertex_Index[2] = *Quantity_vertex - 1;
			}


			verify = Add_Related_Vertex(Massive_Vertex[Temp_Vertex_Index[0]], Massive_Vertex[Temp_Vertex_Index[1]]);
			verify = Add_Related_Vertex(Massive_Vertex[Temp_Vertex_Index[1]], Massive_Vertex[Temp_Vertex_Index[2]]);
			verify = Add_Related_Vertex(Massive_Vertex[Temp_Vertex_Index[0]], Massive_Vertex[Temp_Vertex_Index[2]]);


			fread(&temp_16, sizeof(uint16_t), 1, file_stl);
			verify = false;
		}

		fclose(file_stl);
		return true;
	}
	else
	{
		cout << "File is not found in current directory" << endl;
		return false;
	}

}

float bfs(int start, int end, int* Quantity_vertex, int *length_road, int *Index_way) //Bfs
{

	*length_road = 0;
	bool VisitedPoint[MAX_QUANTITY_VERTEX] = { false };            // for Djekstru
	float DistantPoint[MAX_QUANTITY_VERTEX] = { 0 };       // for Djekstru
	int index_min = 0;
	queue <int> turn;
	for (int i = 0; i<*Quantity_vertex; i++)
		DistantPoint[i] = 999999;
	DistantPoint[start] = 0;
	int index = 0;
	turn.push(start);
	while (!turn.empty())       //while the queue not emptys
	{
		int ind = turn.front();       //get element from queue
		turn.pop();                 //delete from queue

		for (int i = 0; i<Massive_Vertex[ind].Get_count_related_vertex(); i++)      //find the next Vertex
		{
			if (Massive_Vertex[ind].Get_Related_Vertex(i) == end)
			{
				if (DistantPoint[Massive_Vertex[ind].Get_Related_Vertex(i)] != 999999)
					return (DistantPoint[end] + Massive_Vertex[ind].Get_Related_Distance(i));

				else
					return Massive_Vertex[ind].Get_Related_Distance(i);


			}
			else if (Massive_Vertex[ind].Get_Related_Vertex(i) != end && !VisitedPoint[Massive_Vertex[ind].Get_Related_Vertex(i)])
			{
				VisitedPoint[Massive_Vertex[ind].Get_Related_Vertex(i)] = true;
				if (DistantPoint[ind] + Massive_Vertex[ind].Get_Related_Distance(i)<DistantPoint[Massive_Vertex[ind].Get_Related_Vertex(i)])
					index_min = Massive_Vertex[ind].Get_Related_Vertex(i);
				DistantPoint[Massive_Vertex[ind].Get_Related_Vertex(i)] = DistantPoint[ind] + Massive_Vertex[ind].Get_Related_Distance(i);
				turn.push(Massive_Vertex[ind].Get_Related_Vertex(i));            //add vertex to our queue
				if (i + 1 == Massive_Vertex[ind].Get_count_related_vertex() && Index_way[*length_road] != index_min)
				{
					Index_way[*length_road] = index_min;
					*length_road = *length_road + 1;

				}
			}
		}
	}
	return -1;            //if the way !exist

}

int main(int argc, char* argv[])
{


	int pIndex_way[MAX_QUANTITY_VERTEX];
	int *Index_way = pIndex_way;
	int pQuantity_vertex = 0;
	int plength_road = 0; // length way from start to finish
	int *length_road = &plength_road;
	int *Quantity_vertex = &pQuantity_vertex;
	float s_x, s_y, s_z;    //coords start Vertex
	float e_x, e_y, e_z;    //coords end Vertex
	int start = 0;            //index start Vertex
	int end = 0;              //index end Vertex
	bool ifstart = false;     //if start Vertex exist
	bool ifend = false;       //if end Vertex exist
	char ifexit = 'e';        //condition the end of cycle
	string FileName = "wq";


	cout << "Input file name of file that situated in current directory" << endl;
	cout << "For example: 'Model.stl'" << endl;
	getline(cin, FileName);

	if (!InitializationFileStl(FileName, Quantity_vertex))
		return -1;
	do
	{
		ifstart = false;     //if start Vertex exist
		ifend = false;       //if end Vertex exist
		cout << "Input coordinate X start vertex: \n";
		cin >> s_x;
		cout << "Input coordinate Y start vertex: \n";
		cin >> s_y;
		cout << "Input coordinate Z start vertex: \n";
		cin >> s_z;
		cout << "Input coordinate X end vertex: \n";
		cin >> e_x;
		cout << "Input coordinate Y end vertex: \n";
		cin >> e_y;
		cout << "Input coordinate Z end vertex: \n";
		cin >> e_z;
		for (int i = 0; i<*Quantity_vertex; i++)
		{
			if (!ifstart && Massive_Vertex[i].VertexVerify(s_x, s_y, s_z))
			{
				start = i;
				ifstart = true;

				//break;
			}
			if (!ifend && Massive_Vertex[i].VertexVerify(e_x, e_y, e_z))
			{
				end = i;
				ifend = true;

			}
			if (ifstart && ifend)
				break;
		}
		if (!ifstart)
		{
			cout << "Coords start vertex is not exist" << endl;
			//  return -1;
		}
		if (!ifend)
		{
			cout << "Coords end vertex is not exist" << endl;
			//  return -1;
		}



		if (ifstart && ifend)
		{
			float way = bfs(start, end, Quantity_vertex, length_road, Index_way);
			if (way <= 0)
				cout << "Way between Start(" << s_x << ", " << s_y << ", " << s_z << ") and (" << e_x << ", " << e_y << ", " << e_z << ") not exist" << endl;
			else
			{
				cout << "Length of short way=" << way << endl;
				cout << "Road:";
				cout << "PointStart" << "(" << Massive_Vertex[start].Get_x() << ", " << Massive_Vertex[start].Get_y() << ", " << Massive_Vertex[start].Get_z() << ") ---->  ";
				for (int mk = 0; mk<*length_road; mk++)
					cout << "Point" << mk + 1 << "(" << Massive_Vertex[Index_way[mk]].Get_x() << ", " << Massive_Vertex[Index_way[mk]].Get_y() << ", " << Massive_Vertex[Index_way[mk]].Get_z() << ") ---->  ";
				cout << "PointEnd" << "(" << Massive_Vertex[end].Get_x() << ", " << Massive_Vertex[end].Get_y() << ", " << Massive_Vertex[end].Get_z() << ") " << endl;

			}
		}
		ifexit = 'e';
		cout << "Are you want to input coords the next pair of point? \n Input: 'y' - yes or 'n' - no (exit)" << endl;
		while (ifexit != 'y' && ifexit != 'n')
			ifexit = getchar();
	} while (ifexit == 'y');
	for (int i = 0; i<*Quantity_vertex; i++)
		Massive_Vertex[i].~Vertex();
	system("pause");
	return 0;
}