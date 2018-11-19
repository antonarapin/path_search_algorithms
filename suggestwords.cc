#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, char* argv[]){
	string in_file = argv[1];
	string source_word = argv[2];
	int threshold = atoi(argv[3]);

	vector<string> within_thresh;
	int num_within=0;
	ifstream in_f(in_file);
	string file_word;

	while(getline(in_f, file_word)){
		int** table = new int*[source_word.size()+1];
		for(int i=0;i<source_word.size()+1; i++){
			table[i]=new int[file_word.size()+1];
			for(int j=0; j<file_word.size()+1; j++){
				table[i][j]=0;
			}
		}
		for(int i=source_word.size(); i>=0; i--){
			for(int j=file_word.size(); j>=0;j--){
				if(i==source_word.size()){
					table[i][j]=file_word.size()-j;
				} else if(j==file_word.size()){
					table[i][j]=source_word.size()-i;
				} else if(source_word[i]==file_word[j]){
					table[i][j]=table[i+1][j+1];
				} else{
					int minnum=min(min(table[i+1][j+1],table[i+1][j]),table[i][j+1]);
					
					table[i][j] = minnum+1;

				}
			}
		}
		if(table[0][0]<=threshold){
			within_thresh.push_back(file_word);
			num_within+=1;
		}
		
		for(int i=0;i<source_word.size()+1; i++){
			
			delete[] table[i];
			
		}
		delete[] table;

	}
	for(int d =0; d<num_within;d++){
		cout<<within_thresh[d]<<endl;
	}
	return 0;
}