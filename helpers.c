#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int i,j;
    float avg;
    for( i = 0 ; i < height ; i++ )
    {
        for( j = 0 ; j < width ; j++ )
        {
          avg = round( (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);
         if(avg > 255) 
         {
          image[i][j].rgbtRed   = 255;
          image[i][j].rgbtGreen = 255;
          image[i][j].rgbtBlue  = 255;    
         }
         else 
         {
          image[i][j].rgbtRed   = avg;
          image[i][j].rgbtGreen = avg;
          image[i][j].rgbtBlue  = avg;
         }
        }
    }
    return;
}
/*int swap(int a , int b)
{
    int c;
    c=a;
    a=b;
    b=c;
    return b;
}*/
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int i,j,k;
    int temp1[width],temp2[width],temp3[width],temp4[width],temp5[width],temp6[width];
    for( i = 0 ; i < height ; i++ )
    {
        for( k = 0 ; k < width ; k++ )
        {
          temp1[k] = image[i][width-1-k].rgbtRed   ;  
          temp2[k] = image[i][width-1-k].rgbtGreen ;
          temp3[k] = image[i][width-1-k].rgbtBlue  ;  //prepare first variable data
        }
         for( j = 0 ; j < width ; j++ )
        {
          temp4[j] = temp1[j];              //temporary variable will equal second variable
          temp5[j] = temp2[j];
          temp6[j] = temp3[j];
          temp1[j] = image[i][j].rgbtRed;
          temp2[j] = image[i][j].rgbtGreen;
          temp3[j] = image[i][j].rgbtBlue;
          image[i][j].rgbtRed  =temp4[j] ;     //temporary variable will equal to first variable    
          image[i][j].rgbtGreen=temp5[j] ;
          image[i][j].rgbtBlue =temp6[j] ;
        }
    }
    
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int i,j;
    float avg0,avg1,avg2;
    for( i = 0 ; i < height ; i++ )
    {
        for( j = 0 ; j < width ; j++ )
        {
         if( (i==0) && (j==0) )
         {
         avg0 =(image[i][j].rgbtRed+image[i+1][j].rgbtRed +image[i+1][j+1].rgbtRed+image[i][j+1].rgbtRed)/4;
         avg1 =(image[i][j].rgbtGreen+image[i+1][j].rgbtGreen +image[i+1][j+1].rgbtGreen+
         image[i][j+1].rgbtGreen )/4 ;
         avg2 =(image[i][j].rgbtBlue+image[i+1][j].rgbtBlue +image[i+1][j+1].rgbtBlue+
         image[i][j+1].rgbtBlue )/4;
         }
         else if( (i==(height-1)) && (j==(width-1)) )
         {
         avg0 =(image[i][j-1].rgbtRed+image[i-1][j-1].rgbtRed +image[i-1][j].rgbtRed+image[i][j].rgbtRed)/4 ;
         avg1 =(image[i][j-1].rgbtGreen+image[i-1][j-1].rgbtGreen +image[i-1][j].rgbtGreen+
         image[i][j].rgbtGreen )/4 ;
         avg2 =(image[i][j-1].rgbtBlue+image[i-1][j-1].rgbtBlue +image[i-1][j].rgbtBlue+
         image[i][j].rgbtBlue )/4;
         }
         else if( (i==0) && (j==(width-1)) )
         {
         avg0 =(image[i][j-1].rgbtRed+image[i+1][j-1].rgbtRed +image[i+1][j].rgbtRed+image[i][j].rgbtRed)/4 ;
         avg1 =(image[i][j-1].rgbtGreen+image[i+1][j-1].rgbtGreen +image[i+1][j].rgbtGreen+
         image[i][j].rgbtGreen )/4 ;
         avg2 =(image[i][j-1].rgbtBlue+image[i+1][j-1].rgbtBlue +image[i+1][j].rgbtBlue+
         image[i][j].rgbtBlue )/4 ;
         }
         else if( (i==(height-1)) && (j==0) )
         {
         avg0 =(image[i][j+1].rgbtRed+image[i-1][j+1].rgbtRed +image[i-1][j].rgbtRed+image[i][j].rgbtRed)/4;
         avg1 =(image[i][j+1].rgbtGreen+image[i-1][j+1].rgbtGreen +image[i-1][j].rgbtGreen+
         image[i][j].rgbtGreen )/4 ;
         avg2 =(image[i][j+1].rgbtBlue+image[i-1][j+1].rgbtBlue +image[i-1][j].rgbtBlue+
         image[i][j].rgbtBlue )/4 ;
         }
         else if( (i==0) && (j=!0) && (j=! (width-1)) )
         {
         avg0 =(image[i][j-1].rgbtRed+image[i][j].rgbtRed +image[i][j+1].rgbtRed+image[i+1][j].rgbtRed
         +image[i+1][j-1].rgbtRed+image[i+1][j+1].rgbtRed)/6 ;
         avg1 =(image[i][j-1].rgbtGreen+image[i][j].rgbtGreen +image[i][j+1].rgbtGreen+image[i+1][j].rgbtGreen
         +image[i+1][j-1].rgbtGreen+image[i+1][j+1].rgbtGreen)/6;
         avg2 =(image[i][j-1].rgbtBlue+image[i][j].rgbtBlue +image[i][j+1].rgbtBlue+image[i+1][j].rgbtBlue
         +image[i+1][j-1].rgbtBlue+image[i+1][j+1].rgbtBlue)/6 ;
         }
         else if( (i==(height-1)) && (j=!0) && (j=! (width-1)) )
         {
         avg0 =(image[i][j-1].rgbtRed+image[i][j].rgbtRed +image[i][j+1].rgbtRed+image[i-1][j].rgbtRed
         +image[i-1][j-1].rgbtRed+image[i-1][j+1].rgbtRed)/6;
         avg1 =(image[i][j-1].rgbtGreen+image[i][j].rgbtGreen +image[i][j+1].rgbtGreen+image[i-1][j].rgbtGreen
         +image[i-1][j-1].rgbtGreen+image[i-1][j+1].rgbtGreen)/6;
         avg2 =(image[i][j-1].rgbtBlue+image[i][j].rgbtBlue +image[i][j+1].rgbtBlue+image[i-1][j].rgbtBlue
         +image[i-1][j-1].rgbtBlue+image[i-1][j+1].rgbtBlue)/6;
         }
         else if( ((i<=(height-2)) && (i>=1)) && (j==0) )
         {
         avg0 =(image[i][j+1].rgbtRed+image[i][j].rgbtRed +image[i-1][j+1].rgbtRed+image[i-1][j].rgbtRed
         +image[i+1][j+1].rgbtRed+image[i+1][j].rgbtRed)/6;
         avg1 =(image[i][j+1].rgbtGreen+image[i][j].rgbtGreen +image[i-1][j+1].rgbtGreen+image[i-1][j].rgbtGreen
         +image[i+1][j+1].rgbtGreen+image[i+1][j].rgbtGreen)/6;
         avg2 =(image[i][j+1].rgbtBlue+image[i][j].rgbtBlue +image[i-1][j+1].rgbtBlue+image[i-1][j].rgbtBlue
         +image[i+1][j+1].rgbtBlue+image[i+1][j].rgbtBlue)/6 ;
         }
         else if( ((i<=(height-2)) && (i>=1)) && (j==(width-1)) )
         {
         avg0 =(image[i][j-1].rgbtRed+image[i][j].rgbtRed +image[i-1][j-1].rgbtRed+image[i-1][j].rgbtRed
         +image[i+1][j-1].rgbtRed+image[i+1][j].rgbtRed)/6;
         avg1 =(image[i][j-1].rgbtGreen+image[i][j].rgbtGreen +image[i-1][j-1].rgbtGreen+image[i-1][j].rgbtGreen
         +image[i+1][j-1].rgbtGreen+image[i+1][j].rgbtGreen)/6;
         avg2 =(image[i][j-1].rgbtBlue+image[i][j].rgbtBlue +image[i-1][j-1].rgbtBlue+image[i-1][j].rgbtBlue
         +image[i+1][j-1].rgbtBlue+image[i+1][j].rgbtBlue)/6 ;
         }
         else if( ((i<=(height-2)) && (i>=1))  && ((j<=(width-2)) && (j>=1)) )
         {
         avg0 =(image[i][j-1].rgbtRed+image[i][j].rgbtRed +image[i][j+1].rgbtRed+image[i-1][j].rgbtRed
         +image[i-1][j-1].rgbtRed+image[i-1][j+1].rgbtRed+image[i+1][j].rgbtRed
         +image[i+1][j-1].rgbtRed+image[i+1][j+1].rgbtRed)/9 ;
         avg1 =(image[i][j-1].rgbtGreen+image[i][j].rgbtGreen +image[i][j+1].rgbtGreen+image[i-1][j].rgbtGreen
         +image[i-1][j-1].rgbtGreen+image[i-1][j+1].rgbtGreen+image[i+1][j].rgbtGreen
         +image[i+1][j-1].rgbtGreen+image[i+1][j+1].rgbtGreen)/9 ;
         avg2 =(image[i][j-1].rgbtBlue+image[i][j].rgbtBlue +image[i][j+1].rgbtBlue+image[i-1][j].rgbtBlue
         +image[i-1][j-1].rgbtBlue+image[i-1][j+1].rgbtBlue+image[i+1][j].rgbtBlue
         +image[i+1][j-1].rgbtBlue+image[i+1][j+1].rgbtBlue)/9 ;
         }
         image[i][j].rgbtRed   =round(avg0);
         image[i][j].rgbtGreen =round(avg1);
         image[i][j].rgbtBlue  =round(avg2);
         if(avg0 > 255) { image[i][j].rgbtRed  =255;  }
         if(avg1 > 255) { image[i][j].rgbtGreen=255;  }
         if(avg2 > 255) { image[i][j].rgbtBlue =255;  }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
