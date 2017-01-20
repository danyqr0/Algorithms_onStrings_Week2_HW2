//============================================================================
// Name        : Algorithms_onStrings_Week2_HW2.cpp
// Author      : Daniel Ramirez
// Version     :
// Copyright   : HW2_Week2
// Description : Reconstruct a String from its Burrows–Wheeler Transform
//============================================================================

#include <iostream>
using namespace std;

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>

#define Index_$ 0
#define Index_A 1
#define Index_C 1000000
#define Index_G 2000000
#define Index_T 3000000

using namespace std;
using std::string;
using std::vector;
using std::pair;

//prototypes:
string InverseBWT(multimap<long,pair<long,long> > &Ibwt,string &text);
long char_to_index(const char character);
char index_to_char(const long index);

string InverseBWT(multimap<long,pair<long,long> > &Ibwt,string &text) {
  string result = "";
  multimap<long,pair<long,long> >::iterator it_a,_i;
  long _tmp,_index2char;
  //start adding first two chars to result
  it_a=Ibwt.begin();
  _index2char=index_to_char((*it_a).first-1);
  result.push_back(_index2char);

  _index2char=index_to_char(((*it_a).second).first - ((*it_a).second).second);
  result.push_back(_index2char);

  _tmp=((*it_a).second).first;

  for(long i=1;i<text.size();i++){
      _i=Ibwt.find(_tmp);
	  if(_i != Ibwt.end()){
		 _index2char=index_to_char( ((*_i).second).first - ((*_i).second).second);
		 if(_index2char != long('$')) result.push_back(_index2char);
      }
	  _tmp=((*_i).second).first;
  }

  std::reverse(result.begin(),result.end());

  return result;
}

long char_to_index(const char character){
	long _charToIndex;
	switch(character){
					case 'A':
						_charToIndex=Index_A;
						break;
					case 'C':
						_charToIndex=Index_C;
						break;
					case 'G':
						_charToIndex=Index_G;
						break;
					case 'T':
						_charToIndex=Index_T;
						break;
					case '$':
						_charToIndex=Index_$;
						break;
					default:
						break;
	}
	return _charToIndex;
}

char index_to_char(const long index){
    char _indexToChar;

    switch(index){
       case Index_A:
    	   _indexToChar='A';
    	   break;

       case Index_C:
    	   _indexToChar='C';
    	   break;

       case Index_G:
    	   _indexToChar='G';
    	   break;

       case Index_T:
    	   _indexToChar='T';
    	   break;

       case Index_$:
    	   _indexToChar='$';
    	   break;

       default:
    	   _indexToChar=' ';
    	   break;
    }

	return _indexToChar;
}

int main() {

	  string text; string::iterator it_a;
	  long _cA,_cC,_cT,_cG,_c$;
      long _char2index;
	  vector<long> index_sorted; 	  vector<long>::iterator it_e;
	  vector<pair<long,long> > _high;  vector<pair<long,long> >::iterator it_d;
	  multimap<long,pair<long,long> > Ibwt;

	  cin >> text;

	  _cA=0;_cC=0;_cT=0;_cG=0;_c$=0;

      if(text.size()>=1 && text.size()<=1000000){
         for(it_a=text.begin();it_a!=text.end();++it_a){
           if((*it_a) == 'A' || (*it_a) == 'C' || (*it_a) == 'T' || (*it_a) == 'G' || (*it_a) == '$'){
        	 switch(*it_a){
        		case 'A':
        			++_cA;
                    _char2index=char_to_index('A');
        			index_sorted.push_back(_char2index+_cA);
        			_high.push_back(make_pair(_char2index+_cA,_cA));
        			break;

        		case 'C':
        			++_cC;
                    _char2index=char_to_index('C');
        			index_sorted.push_back(_char2index+_cC);
        			_high.push_back(make_pair(_char2index+_cC,_cC));
        		    break;

        		case 'T':
        			++_cT;
                    _char2index=char_to_index('T');
        			index_sorted.push_back(_char2index+_cT);
        			_high.push_back(make_pair(_char2index+_cT,_cT));
        		    break;

        		case 'G':
        			++_cG;
                    _char2index=char_to_index('G');
        			index_sorted.push_back(_char2index+_cG);
        			_high.push_back(make_pair(_char2index+_cG,_cG));
        		    break;

        		case '$':
        			++_c$;
                    _char2index=char_to_index('$');
        			index_sorted.push_back(_char2index+_c$);
        			_high.push_back(make_pair(_char2index+_c$,_c$));
        		    break;

        		default:
        			break;
        	 }
           }
         }

         std::sort(index_sorted.begin(),index_sorted.end());

         it_d=_high.begin();
         for(it_e=index_sorted.begin();it_e!=index_sorted.end();++it_e,++it_d)
        	 Ibwt.insert(make_pair((*it_e),make_pair((*it_d).first,(*it_d).second)));

         cout<<InverseBWT(Ibwt,text)<<endl;
      }
	  return 0;
}
