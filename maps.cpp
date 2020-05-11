#include<iostream>
#include<limits.h>
#include<map>
#include<string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
int adjMat[1000][1000];
string road[1000][1000];
int v=53;
bool visit[1000];
int dist[1000];
int list[1000];
map<string,int>place;

int minDis(){
	int min=INT_MAX; int min_index;
	for(int a=0;a<v;a++){
		if(!visit[a]&&dist[a]<=min){
			min=dist[a]; min_index=a;
		}
	}
	return min_index;
}

void djikstra(int src,int end){
	for(int a=0;a<v;a++){
		dist[a]=INT_MAX; visit[a]=false;
	}
	dist[src]=0;
	for(int count=0;count<v-1;count++){
		int u=minDis();
		visit[u]=true;
		if(u==end) break;
		for(int a=0;a<v;a++){
			if(!visit[a]&&adjMat[u][a]&&dist[u]!=INT_MAX&&dist[u]+adjMat[u][a]<dist[a]){
				dist[a]=dist[u]+adjMat[u][a];
				list[a]=u;
			}
				
		}
	}
}

void search(string src,string end){
	memset(visit,0,sizeof(visit));
	memset(dist,0,sizeof(visit));
	memset(list,0,sizeof(visit));

	int p2=place[src];
	int p1=place[end];
	djikstra(p1,p2);
	int temp=p2;
	string ans;
	while(temp!=p1){
		cout<<road[temp][list[temp]]<<endl;
		temp=list[temp];
	}
}

void fileInput() {
	FILE *input = fopen("test.txt", "r");
	if(input == NULL) {
		cout << "File not found 1\n";
		return;
	}
	int a, b, w;
	char arr[1000];
	
	while(!feof(input)) {
		fscanf(input, "%d#%d#%d#%[^\n]\n", &a, &b, &w, arr);
		string str = "";
		int len = strlen(arr);
		for(int a1 = 0; a1 < len; ++a1) str += arr[a1];
		adjMat[a][b] = w;
		adjMat[b][a] = w;
		road[a][b] = str;
		road[b][a] = str;
	}
	
	fclose(input);	
}

void fileInput2() {
	FILE *input = fopen("apaaja.txt", "r");
	if(input == NULL) {
		cout << "File not found 2\n";
		return;
	}
	int a, b, w;
	char arr[1000];
	
	while(!feof(input)) {
		fscanf(input, "%[^#]#%d\n", &arr, &a);
		string str = "";
		int len = strlen(arr);
		for(int a1 = 0; a1 < len; ++a1) str += arr[a1];
		place.insert(pair<string,int>(str,a));
		
	}
	fclose(input);
}

void printMenu() {
	cout << "================\n";
	cout << "      GGPS      \n";
	cout << "================\n";
	
	cout << "1. Show available places\n";
	cout << "2. Start navigation\n";
	cout << "3. Exit\n";
}

void printPlaces() {
	cout<<"yes"<<endl;
	for(map<string, int>::iterator it = place.begin(); it != place.end(); it++) {
		cout << it->second << ". " << it->first << endl;
	}
}

int main(){
	int opt;
	string str,str2;
	bool locFound;
	fileInput();
	fileInput2();
	do {
		printMenu();
		
		cin >> opt;
		
		switch(opt) {
			case 1 : {
				printPlaces();			
				break;
			}
			case 2: {
				do {
					locFound = 0;
					printPlaces();
					cout << "Insert starting location: ";
					cin.clear(); cin.sync();
					cin >> str;
					
				}while(!place[str]);
				
				do {
					locFound = 0;
					printPlaces();
					cout << "Insert end point: ";
					cin.clear(); cin.sync();
					cin >> str2;
					
				}while(!place[str2]);
				search(str,str2);
				getchar();
			}
		}
	}while(opt != 3);
	
	//search("Binus ASO","FX Sudirman");
}
