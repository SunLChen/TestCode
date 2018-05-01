 ///
 /// @file    spilteWorld.cc
 /// @author  cgy(cgy@qq.com)
 /// @date    2018-04-30 19:04:33
 ///
 
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <set>
#include <map>
#include <sstream>
#include <regex>
using namespace std;

class World{
	public:
		World(){cout<<"World()"<<endl;};
		~World(){cout<<"~World()"<<endl;};
		void read(string &filename);
		void query(string & world);
	private:
		string & replaceSympol(string & line);
	private:
		vector<string> _worldLine;
		map<string,set<int>> _worldl;
		map<string,int> _countWorld;
};
void World::read(string & filename){
	shared_ptr<ifstream> pifs(new ifstream(filename),[](ifstream *p){
				if(p){
					p->close();
				}
			});
	if(!pifs){
		cout<<"ifstream open error"<<endl;
		return;
	}
	int i=0;
	for(string line;getline(*pifs,line);i++){
		string world;
		_worldLine.push_back(line);
		line = replaceSympol(line);
		istringstream input(line);
	//	_worldLine.push_back(replaceSympol(line));
		while(input>>world){
			//统计词频
			++_countWorld[world];
			//统计所出现的行数
			auto it=_worldl.find(world);
			if(it!=_worldl.end()){
				it->second.insert(i);
			}else{
				set<int> temp={i};
				_worldl.insert(make_pair(world,temp));
			}
		}
	}

}
void World::query(string & world){

	cout<<"\""<<world<<"\" occurs "<<_countWorld[world]<<" times"<<endl;
	auto it=_worldl.find(world);
	if(_worldl.end()!=it){
		for(auto i:it->second){
			cout<<"\tline ("<<i+1<<")"<<_worldLine[i]<<endl;	
		}	
	}
}
string & World::replaceSympol(string & line){
	shared_ptr<regex> e(new regex("[^a-zA-Z']"));
	string s;
	regex_replace(back_inserter(s),line.begin(),line.end(),*e,"");
	return (line=s);
}

int main(void){
	shared_ptr<World> w(new World());
	string filename="china_daily.txt";
	string queryWorld("work");
	w->read(filename);
	w->query(queryWorld);
	return 0;
}
