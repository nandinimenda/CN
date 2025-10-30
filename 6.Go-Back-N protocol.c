#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX_FRAMES 50
#define WINDOW_SIZE 4
int is_frame_lost()
{
    return(rand()%5) == 0;
}
int main()
{
    int total_frames,sent=0,ack=0,to_send,i;
    srand((unsigned)time(NULL));
    printf("Enter total no.of frames to send(max%d)",MAX_FRAMES);
    scanf("%d",&total_frames);
    printf("\n sending frames using Go-Back-N with window size %d\n",WINDOW_SIZE);
    while(ack < total_frames)
    {
        to_send = 0;
        for(i=0;i<WINDOW_SIZE&&sent+i<total_frames;i++)
          to_send++;
        printf("\nsender window: [");
        for(i=0;i<to_send;i++)
          printf("%d",sent+i+1);
        printf("]\n");
        int error_index = -1;
        for(i=0;i<to_send;i++)
        {
            if(is_frame_lost())
            {
                printf("frames %d lost or corrupted!\n",sent+i+1);
                error_index = i;
                break;
            }
            else
            {
                printf("frame %d sent successfully.\n",sent+i+1);
            }
        }
        if(error_index == -1)
        {
            printf("Receiver: ACK for all %d frames",to_send);
            sent += to_send;
            ack += to_send;
        }
        else
        {
            printf("Receiver: NACK for frame %d.Go-Back-N triggered.",sent+error_index+1);
            printf("Receiver: Discards all frames after and incl.frame%d",sent+error_index+1);
            sent += error_index;
            ack += error_index;
        }
    }
    printf("\nAll frames sent and acknowledged successfully.\n");
    return 0;
}
