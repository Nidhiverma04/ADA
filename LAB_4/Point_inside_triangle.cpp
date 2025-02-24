#include<iostream>
#include<random>
#include<ctime>
using namespace std;

void generate_vertices(int** vertices){
    for(int i =0;i<3;i++)
        vertices[i] = new int[2];

    for(int i = 0;i<3;i++){
        for(int j =0;j<2;j++){
            vertices[i][j] = rand()%10;
        }
    }
    return;
}

double area(int x1, int y1, int x2, int y2, int x3, int y3){
    //area using determinant method
    return abs((x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2)) / 2.0);
}

bool isInside(int** v, int px, int py){
    double A = area(v[0][1], v[0][1], v[1][0], v[1][1], v[2][0], v[2][1]);
    double A1 = area(px, py, v[1][0], v[1][1], v[2][0], v[2][1]);
    double A2 = area(v[0][1], v[0][1], px, py, v[2][0], v[2][1]);
    double A3 = area(v[0][1], v[0][1], v[1][0], v[1][1], px, py);

    cout<<"\nA = "<<A;
    cout<<"\nA1 + A2 + A3 = "<<A1+A2+A3<<endl;
    return (A == (A1+A2+A3));
}

int main(){
    
    srand(time(0));
    int** vertices = new int*[3];
    
    int px = rand()%8;
    int py = rand()%10;
    generate_vertices(vertices);
    
    cout<<"Vertices : \n";
    for(int i=0;i<3;i++){
        cout<<"( "<<vertices[i][0]<<", "<<vertices[i][1]<<" )"<<endl;
    }
    if(isInside(vertices, px, py)){
        cout<<"\n( "<<px<<", "<<py<<" ) is inside the triangle.";
    }
    else{
        cout<<"\n( "<<px<<", "<<py<<" ) is outside the triangle.";
    }

}

// Vertices : 
// ( 9, 7 )
// ( 2, 5 )
// ( 1, 9 )
// ( 6, 7 ) is inside the triangle.