/*
ARC cache replacement algorithm
Implemented by:
Anuj Rai (2019AIM1003)
Mahip Soni (2019AIM1006)
for CS-604(Advanced Operating System) Group Project Work
Reference Paper:
Megiddo, N. and Modha, D.S., 2004. Outperforming LRU with an adaptive replacement cache algorithm. Computer, 37(4), pp.58-65.
*/

#include<bits/stdc++.h>
#define HASHSIZE 1000000
using namespace std;

//creating a hash file through array
unsigned int Hash[HASHSIZE];

//we use vector(dynamic array) data structures to represent queues.
/*
A ARC Cache consisting of 4 Queues
 mrug (B1)- Most Recently Used Ghost
 mru (T1) - Most Recently Used
 mfu (T2) - Most Frequently Used
 mfug (B2) - Most Frequently Used Ghost
*/

vector<unsigned int> mrug, mru, mfu, mfug;

float p=0.0;
unsigned int c,cnt=0;
unsigned int HitCount=0, MissCount=0;
//Global cache size, taken as input by user
unsigned int cacheSize;

//A function to check whether Page x is available in 'v' queue
int check(vector<unsigned int> v, unsigned int x)
{
    unsigned int l=v.size(),i;
    for(i=0;i<l;i++)
    {
        if(v[i]==x)
            return 1;
    }
    return 0;
}

//A function to insert page 'i' in 'v' queue.
void queue_insert(vector<unsigned int>& v, unsigned int i)
{
    if(v.size()==cacheSize)
        v.erase(v.begin());
    v.push_back(i);
}

//function to pop LRU element from queue 'v'
void queue_delete(vector<unsigned int>& v)
{
    if(v.size()>0)
        v.erase(v.begin());
}


//function to move a particular page from one queue to another, 'x' from queue 'v' to queue 'w'
void movefrom(vector<unsigned int>& v, vector<unsigned int>& w, int x)
{
    int i,j,l=v.size();
    for(i=0;i<l;i++)
        if(v[i]==x)
           {
            v.erase(v.begin()+i);
            break;
        }

        if(w.size()==cacheSize)
            w.erase(w.begin());
        w.push_back(x);
}

/*
Replace subroutine as specified in the reference paper
This function is called when a page with given 'pageNumber' is to be moved from
T2 to B2 or T1 to B1. Basically this function is used to move the elements out from
one list and add it to the another list beginning.
*/
void Replace(const unsigned int i, const float p)
{
	if (( mru.size() >= 1) && (( mru.size() >  p) || (check( mfug,i)) && ( p ==  mru.size())))
	{
		if ( mru.size()>0)
		{
			movefrom( mru,  mrug,  mru[0]);
		}
	}
	else
	{
		if ( mfu.size()>0)
		{
			movefrom( mfu,  mfug,  mfu[0]);
		}
	}
}

//function to look object through given key.
void arc_lookup(unsigned int i)
{
    if (Hash[i%HASHSIZE] > 0)
    {
        //Case 1: Page found in MRU
        if(check( mru,i))
        {
            HitCount++;
            movefrom( mru, mfu,i);
        }
        //Case 1: Part B:Page found in MFU
        else if(check( mfu,i))
        {
            HitCount++;
            movefrom( mfu, mfu,i);
        }
        //Case 2: Page found in MRUG
        else if(check( mrug,i))
        {
            MissCount++;
            p=(float)min((float)c, (float)(p + max((mfug.size()*1.0) / mrug.size(), 1.0)));
            Replace(i, p);
            movefrom( mrug, mfu,i);
        }
        //Case 3: Page found in MFUG
        else if(check( mfug,i))
        {
            MissCount++;
            p=(float)max((float)0.0, (float)(p - max((mrug.size()*1.0) / mfug.size(), 1.0)));
            Replace(i, p);
            movefrom( mfug, mfu,i);
        }

        //Case 4:  Page not found in any of the queues.
        else{
        MissCount++;
        //Case 4: Part A: When L1 has c pages
    		if (( mru.size() +  mrug.size()) ==  c)
    		{
    			if ( mru.size() <  c)
    			{
    				Hash[ mrug[0]% HASHSIZE]--;


    				queue_delete( mrug);
    				Replace(i, p);
    			}
    			else
    			{

    				Hash[ mru[0]% HASHSIZE]--;

    				queue_delete( mru);
    			}
    		}
    		// Case 4: Part B: L1 has less than c pages
    		else if (( mru.size() +  mrug.size()) <  c)
    		{
    			if (( mru.size() +  mfu.size() +  mrug.size() +  mfug.size()) >=  c)
    			{
    				if (( mru.size() +  mfu.size() +  mrug.size() +  mfug.size()) == (2 *  c))
    				{

    					Hash[ mfug[0] % HASHSIZE]--;

    					queue_delete( mfug);
    				}
    				Replace(i,  p);
    			}

		    }
		//Move the page to the most recently used position
		  queue_insert( mru, i);
		  Hash[i % HASHSIZE]++;
      }
    }

    else{
      //Page not found, increase miss count
      MissCount++;

      //Case 4: Part A: L1 has c pages
      if((mru.size()+mrug.size())==c){
        if(mru.size()<c){
          Hash[mrug[0]%HASHSIZE]--;

          queue_delete(mrug);
          Replace(i, p);
        }

        else{
          Hash[mru[0]%HASHSIZE]--;
          queue_delete(mru);
        }
      }

      //Case 4: Part B: L1 less than c pages
      else if((mru.size()+mrug.size())<c){
        if((mru.size()+mfu.size()+mrug.size()+mfug.size())>=c){
          if((mru.size()+mfu.size()+mrug.size()+mfug.size())==2*c){
            Hash[mfug[0]%HASHSIZE]--;

            queue_delete(mfug);
        }
        Replace(i,p);
      }
    }

    //Move the page to the most recently used position
    queue_insert( mru, i);
    Hash[i % HASHSIZE]++;
  }
}

int main()
{
    //input and output file names
    //char ipFileName[100], opFileName[100];

    //scanf("%s %s",ipFileName,opFileName);

    //cache size input from the user
    //cin>>cacheSize;
    char ipFileName[8][100]={"P12.lis"}, opFileName[100]="DemoARC.txt";
    int x,y;
    for(x=0;x<8;x++)
    {
    for(y=32;y<=4096;y*=2)
    {   printf("%s %d\n",ipFileName[x],y);
        cacheSize=y;
        MissCount=0,HitCount=0;

    //time variables, to calculate runtime
    time_t start,stop;

    //opening the trace file
    FILE *fp=fopen(ipFileName[x], "r");
    if(!fp)
    {
    printf("Error opening file: %s\n", ipFileName);
    exit(EXIT_FAILURE);
    }

    unsigned int iStartingBlock = 0, iNumberOfBlocks = 0, iIgnore = 0, iRequestNumber = 0;
    unsigned int i=0;
    time(&start);
    p=0;
    c=cacheSize;

	while (fscanf(fp, "%u %u %u %u", &iStartingBlock, &iNumberOfBlocks, &iIgnore, &iRequestNumber)!=-1)
	{       //printf("%u\n",cnt++);
			for (i = iStartingBlock; i < (iStartingBlock + iNumberOfBlocks); i++)
			{
				arc_lookup(i);

			}
	}

	time(&stop);
	fclose(fp);
	fp=fopen(opFileName,"a");
	fprintf(fp,"%s %d\n",ipFileName[x],y);
	fprintf(fp,"%u %u\n",MissCount,HitCount);
	fprintf(fp,"Hit Ratio = %5.4f %%\n", ((float)(HitCount * 100) / (HitCount + MissCount)));
	fprintf(fp,"Rounded Hit Ratio = %5.2f %%\n", floor(((float)(HitCount * 100) / (HitCount + MissCount)) * 100 + 0.5) / 100);
	fprintf(fp,"Finished in about %.0f seconds. \n", difftime(stop, start));
	fclose(fp);
	mru.clear();
	mfu.clear();
	mrug.clear();
	mfug.clear();
	for(i=0;i<HASHSIZE;i++)
        Hash[i]=0;
    }
    }
    return 0;
}
