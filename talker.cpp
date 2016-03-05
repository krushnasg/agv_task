#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "geometry_msgs/Point.h"
#include <iostream>
#include <string>
#include "ros/ros.h"
#include <cv_bridge/cv_bridge.h>
#include<stack>
#include<opencv2/imgproc/imgproc.hpp>

//! [includes]

//! [namespace]
using namespace cv;
//! [namespace]

using namespace std;
struct pt{
 int x;
int y;
};

typedef struct pt Pt;
Pt findStart(Mat image);
Pt findEnd(Mat image);
Pt nextCood(Pt p, Pt end,Mat image);



Pt* path;


void DFS(Pt start,Pt end,Mat image)
{
  int i,j,k=0;
  stack<Pt> s;
  s.push(start);
  Pt cnt[200][200],A,temp;
int visit[200][200];
  while(!s.empty())
    {
      A=s.top();
      s.pop();
      visit[A.x][A.y]=1;
      for(i=1;i>-2;i--)
	{
	  for(j=1;j>2;j--)
	    {
	      temp.x=A.x+i;
	      temp.y=A.y+j;
	      if(temp.x<200 && temp.y<200 && temp.x>=0 && temp.y>=0){
	      if(temp.x==end.x && temp.y==end.y)
		{(cnt[end.x][end.y]).x=A.x;
		  (cnt[end.x][end.y]).y=A.y;
		   break;}
		  else if(image.at<Vec3b>(temp.x,temp.y)[0]==255 && image.at<Vec3b>(temp.x,temp.y)[1]==255 && image.at<Vec3b>(temp.x,temp.y)[2]==255)
		    visit[temp.x][temp.y]=1;
		  else if( visit[temp.x][temp.y]!=1)
		    {s.push(temp);
		      (cnt[temp.x][temp.y]).x=A.x;
                      (cnt[temp.x][temp.y]).y=A.y;
		    }
                }
	    }
if(temp.x==end.x && temp.y==end.y)
		{(cnt[end.x][end.y]).x=A.x;
		  (cnt[end.x][end.y]).y=A.y;
		   break;}
	}
if(temp.x==end.x && temp.y==end.y)
		{(cnt[end.x][end.y]).x=A.x;
		  (cnt[end.x][end.y]).y=A.y;
		   break;}
    }
 i=end.x;
 j=end.y;
 while((cnt[i][j]).x!=start.x && (cnt[i][j]).y!=start.y)
   {
     (*(path+k)).x=(cnt[i][j]).x;
     (*(path+k)).y=(cnt[i][j]).y;
     i=(cnt[i][j]).x;
    j=(cnt[i][j]).y;
    k++;
   }

}







int main( int argc, char** argv )
{
    //! [load]
    string imageName("/home/vivek/Downloads/agv_task-master/pic2.png"); // by default
    if( argc > 1)
    {
        imageName = argv[1];
    }
    //! [load]

    //! [mat]
    Mat image;
    //! [mat]

    //! [imread]
    image = imread(imageName.c_str(), IMREAD_COLOR); // Read the file
    //! [imread]

    if( image.empty() )                      // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    //! [window]
 //   namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
    //! [window]

    //! [imshow]
//    imshow( "Display window", image );                // Show our image inside it.
    //! [imshow]

    //! [wait]
  //  waitKey(0); // Wait for a keystroke in the window
    //! [wait]


    //	Pt path[1000],p;
        Pt p;
	int k=0,i=0;
	Pt start,end;
	start=findStart(image);
	end=findEnd(image);
	cout<<"("<<start.x<<","<<start.y<<") ; ("<<end.x<<","<<end.y<<")"<<endl;
	/*while (p.x!=end.x && p.y!=end.y)
	{
		p=nextCood(p,end,image);
		path[k]=p;
		k++;
		}*/
	k=0;
	DFS(start,end,image);
	while((*(path+k)).x!=start.x && (*(path+k)).y!=start.y)
	  {
	    cout<<"("<<(*(path+k)).x<<","<<(*(path+k)).y<<")"<<endl;
	    k++;
	  }
	


ros::init(argc, argv, "talker");
 ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<geometry_msgs::Point>("chatter", 1000);
ros::Rate loop_rate(10);

while(i < k)
{
	geometry_msgs::Point pnt;
	pnt.x = (*(path+i)).x;
	pnt.y = (*(path+i)).y;
	chatter_pub.publish(pnt);
    ros::spinOnce();
    loop_rate.sleep();
    i++;
}


	
    return 0;
}

Pt findStart(Mat image)
{
int i,j,k=0;
Pt A[4000],start;
start.x=0;
start.y=0;
for(i=0;i<200;i++)
{
	for(j=0;j<200;j++)
	{
		if(image.at<Vec3b>(i,j)[0]<50 && image.at<Vec3b>(i,j)[2]>200 && image.at<Vec3b>(i,j)[1]<50)
		{
			A[k].x=i;
			A[k].y=j;
			k++;
		}
	}
}
for(i=0;i<k;i++)
{
	start.x=start.x + A[i].x;
	start.y=start.y + A[i].y;	
}
start.x=start.x/k;
start.y=start.y/k;
return start;
}



Pt findEnd(Mat image)
{
int i,j,k=0;
Pt A[4000],end;
end.x=0;
end.y=0;
for(i=0;i<200;i++)
{
	for(j=0;j<200;j++)
	{
		if(image.at<Vec3b>(i,j)[0]<50 && image.at<Vec3b>(i,j)[1]>200 && image.at<Vec3b>(i,j)[2]<50)
		{
			A[k].x=i;
			A[k].y=j;
			k++;
		}
	}
}
for(i=0;i<k;i++)
{
	end.x=end.x + A[i].x;
	end.y=end.y + A[i].y;	
}
end.x=end.x/k;
end.y=end.y/k;
return end;
}


