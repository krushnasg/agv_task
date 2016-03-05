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


void Dfs(Pt start,Pt end)
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
	      if(temp.x==end.x && temp.y==end.y)
		{(cnt[end.x][end.y]).x=A.x;
		  (cnt[end.x][end.y]=A.y;
		   break;}
		  else if(image.at<Vec3b>(temp.x,temp.y)[0]==255 && image.at<Vec3b>(temp.x,temp.y)[1]==255 && image.at<Vec3b>(temp.x,temp.y)[2]==255)
		    visit[temp.x][temp.y]=1;
		  else if( visit[temp.x][temp.y]!=1)
		    {s.push(temp);
		      (cnt[temp.x][temp.y]).x=A.x;
                      (cnt[temp.x][temp.y]).y=A.y;
		    }

	    }
if(temp.x==end.x && temp.y==end.y)
		{(cnt[end.x][end.y]).x=A.x;
		  (cnt[end.x][end.y]=A.y;
		   break;}
	}
if(temp.x==end.x && temp.y==end.y)
		{(cnt[end.x][end.y]).x=A.x;
		  (cnt[end.x][end.y]=A.y;
		   break;}
    }
 i=end.x;
 j=end.y;
 while(cnt[i][j]!=NULL)
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
    string imageName("/home/krushna/catkin_ws/src/agv_task/src/pic2.png"); // by default
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
	k=0
	DFS(start,end);
	while(*(path+k)!=NULL)
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
Pt A[1000],start;
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
Pt A[1000],end;
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


/*Pt nextCood(Pt p, Pt end,Mat image)
{
Pt p2;
int count=0;	
if(p.x-end.x<2 && p.y-end.y<2 && p.x-end.x>-2 && p.y-end.y>-2)
return end;
if(p.y-end.y>0.414*(p.x-end.x) && p.y-end.y<(p.x-end.x)/0.414)
{
	p2.x=p.x+1;
	p2.y=p.y+1;
	while(image.at<Vec3b>(p2.x,p2.y)[0]==255 && image.at<Vec3b>(p2.x,p2.y)[1]==255 && image.at<Vec3b>(p2.x,p2.y)[2]==255)
	{
		p2.x=p.x+1;
		p2.y=p.y+1;		
		switch (count)
		{
			case 0:p2.x=p2.x-1;break;
			case 1:p2.y=p2.y-1;break;
			case 2:p2.x=p2.x-2;break;
			case 3:p2.y=p2.y-2;break;
			case 4:{p2.x=p2.x-2;
				p2.y=p2.y-1;}break;
			case 6:{p2.y=p2.y-2;
				p2.x=p2.x-2;}break;
			case 5:{p2.y=p2.y-2;
				p2.x=p2.x-1;}break;
			case 8:{p2.x=p2.x-1;
				p2.y=p2.y-1;}break;
		}
		
		count++;
	}

}
else if(p.y-end.y<0.414*(p.x-end.x) && p.y-end.y<(p.x-end.x)/0.414)
{
	p2.x=p.x+1;
	//p2.y=p.y+1;
count=0;
	while(image.at<Vec3b>(p2.x,p2.y)[0]==255 && image.at<Vec3b>(p2.x,p2.y)[1]==255 && image.at<Vec3b>(p2.x,p2.y)[2]==255)
	{
		p2.x=p.x+1;
		p2.y=p.y+1;

		switch (count)
		{
			case 0:p2.x=p2.x-1;break;
			case 1:p2.y=p2.y-1;break;
			case 2:p2.x=p2.x-2;break;
			case 3:p2.y=p2.y-2;break;
			case 4:{p2.x=p2.x-2;
				p2.y=p2.y-1;}break;
			case 6:{p2.y=p2.y-2;
				p2.x=p2.x-2;}break;
			case 5:{p2.y=p2.y-2;
				p2.x=p2.x-1;}break;
			case 8:{p2.x=p2.x-1;
				p2.y=p2.y-1;}break;
		}
		
		count++;
	}

}
else if(p.y-end.y>0.414*(p.x-end.x) && p.y-end.y>(p.x-end.x)/0.414)
{
	//p2.x=p.x+1;
	p2.y=p.y+1;
count=0;
	while(image.at<Vec3b>(p2.x,p2.y)[0]==255 && image.at<Vec3b>(p2.x,p2.y)[1]==255 && image.at<Vec3b>(p2.x,p2.y)[2]==255)
	{
		p2.x=p.x+1;
		p2.y=p.y+1;		
		switch (count)
		{
			case 0:p2.x=p2.x-1;break;
			case 1:p2.y=p2.y-1;break;
			case 2:p2.x=p2.x-2;break;
			case 3:p2.y=p2.y-2;break;
			case 4:{p2.x=p2.x-2;
				p2.y=p2.y-1;}break;
			case 6:{p2.y=p2.y-2;
				p2.x=p2.x-2;}break;
			case 5:{p2.y=p2.y-2;
				p2.x=p2.x-1;}break;
			case 8:{p2.x=p2.x-1;
				p2.y=p2.y-1;}break;
		}
		
		count++;
	}

}

}*/
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


void Dfs(Pt start,Pt end)
{
  int i,j,k=0;
  stack<Pt> s;
  s.push(start);
  Pt visit[200][200],cnt[200][200],A,temp;
  while(!s.empty())
    {
      A=s.top();
      s.pop();
      visit[A.x][A.y]=1;
      for(i=1;i>-2:i--)
	{
	  for(j=1;j>2;j--)
	    {
	      temp.x=A.x+i;
	      temp.y=A.y+j;
	      if(temp.x==end.x && temp.y==end.y)
		{(cnt[end.x][end.y]).x=A.x;
		  (cnt[end.x][end.y]=A.y;
		   break;}
		  else if(image.at<Vec3b>(temp.x,temp.y)[0]==255 && image.at<Vec3b>(temp.x,temp.y)[1]==255 && image.at<Vec3b>(temp.x,temp.y)[2]==255)
		    visit[temp.x][temp.y]=1;
		  else if( visit[temp.x][temp.y]!=1)
		    {s.push(temp);
		      (cnt[temp.x][temp.y]).x=A.x;
                      (cnt[temp.x][temp.y]).y=A.y;
		    }

	    }
if(temp.x==end.x && temp.y==end.y)
		{(cnt[end.x][end.y]).x=A.x;
		  (cnt[end.x][end.y]=A.y;
		   break;}
	}
if(temp.x==end.x && temp.y==end.y)
		{(cnt[end.x][end.y]).x=A.x;
		  (cnt[end.x][end.y]=A.y;
		   break;}
    }
 i=end.x;
 j=end.y;
 while(cnt[i][j]!=NULL)
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
    string imageName("/home/krushna/catkin_ws/src/agv_task/src/pic2.png"); // by default
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
	k=0
	DFS(start,end);
	while(*(path+k)!=NULL)
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
	pnt.x = path[i].x;
	pnt.y = path[i].y;
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
Pt A[1000],start;
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
Pt A[1000],end;
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


/*Pt nextCood(Pt p, Pt end,Mat image)
{
Pt p2;
int count=0;	
if(p.x-end.x<2 && p.y-end.y<2 && p.x-end.x>-2 && p.y-end.y>-2)
return end;
if(p.y-end.y>0.414*(p.x-end.x) && p.y-end.y<(p.x-end.x)/0.414)
{
	p2.x=p.x+1;
	p2.y=p.y+1;
	while(image.at<Vec3b>(p2.x,p2.y)[0]==255 && image.at<Vec3b>(p2.x,p2.y)[1]==255 && image.at<Vec3b>(p2.x,p2.y)[2]==255)
	{
		p2.x=p.x+1;
		p2.y=p.y+1;		
		switch (count)
		{
			case 0:p2.x=p2.x-1;break;
			case 1:p2.y=p2.y-1;break;
			case 2:p2.x=p2.x-2;break;
			case 3:p2.y=p2.y-2;break;
			case 4:{p2.x=p2.x-2;
				p2.y=p2.y-1;}break;
			case 6:{p2.y=p2.y-2;
				p2.x=p2.x-2;}break;
			case 5:{p2.y=p2.y-2;
				p2.x=p2.x-1;}break;
			case 8:{p2.x=p2.x-1;
				p2.y=p2.y-1;}break;
		}
		
		count++;
	}

}
else if(p.y-end.y<0.414*(p.x-end.x) && p.y-end.y<(p.x-end.x)/0.414)
{
	p2.x=p.x+1;
	//p2.y=p.y+1;
count=0;
	while(image.at<Vec3b>(p2.x,p2.y)[0]==255 && image.at<Vec3b>(p2.x,p2.y)[1]==255 && image.at<Vec3b>(p2.x,p2.y)[2]==255)
	{
		p2.x=p.x+1;
		p2.y=p.y+1;

		switch (count)
		{
			case 0:p2.x=p2.x-1;break;
			case 1:p2.y=p2.y-1;break;
			case 2:p2.x=p2.x-2;break;
			case 3:p2.y=p2.y-2;break;
			case 4:{p2.x=p2.x-2;
				p2.y=p2.y-1;}break;
			case 6:{p2.y=p2.y-2;
				p2.x=p2.x-2;}break;
			case 5:{p2.y=p2.y-2;
				p2.x=p2.x-1;}break;
			case 8:{p2.x=p2.x-1;
				p2.y=p2.y-1;}break;
		}
		
		count++;
	}

}
else if(p.y-end.y>0.414*(p.x-end.x) && p.y-end.y>(p.x-end.x)/0.414)
{
	//p2.x=p.x+1;
	p2.y=p.y+1;
count=0;
	while(image.at<Vec3b>(p2.x,p2.y)[0]==255 && image.at<Vec3b>(p2.x,p2.y)[1]==255 && image.at<Vec3b>(p2.x,p2.y)[2]==255)
	{
		p2.x=p.x+1;
		p2.y=p.y+1;		
		switch (count)
		{
			case 0:p2.x=p2.x-1;break;
			case 1:p2.y=p2.y-1;break;
			case 2:p2.x=p2.x-2;break;
			case 3:p2.y=p2.y-2;break;
			case 4:{p2.x=p2.x-2;
				p2.y=p2.y-1;}break;
			case 6:{p2.y=p2.y-2;
				p2.x=p2.x-2;}break;
			case 5:{p2.y=p2.y-2;
				p2.x=p2.x-1;}break;
			case 8:{p2.x=p2.x-1;
				p2.y=p2.y-1;}break;
		}
		
		count++;
	}

}

}*/

