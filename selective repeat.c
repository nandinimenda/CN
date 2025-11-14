#include<stdio.h>
#include<stdlib.h>
#define MAX_FRAMES 10
typedef struct
{
    int frame_no;
    int acked;
}Frame;
void send_frame(int frame_no)
{
    printf("Sender: sent frame %d\n",frame_no);
}
void receive_frame(int frame_no)
{
    printf("Receiver: Receiced frame %d\n",frame_no);
}
void send_ack(int frame_no)
{
    printf("Receiver: ACK sent for frame %d\n",frame_no);
}
void receive_ack(int frame_no)
{
    printf("Sender: ACK received for frame %d\n",frame_no);
}
int main()
{
    int total_frames,window_size;
    int sender_base = 0;
    int next_frame_to_send = 0;
    int receiver_expected = 0;
    int ack[MAX_FRAMES] = {0};
    Frame window[MAX_FRAMES];
    printf("Enter total no.of frames to send:");
    scanf("%d",&total_frames);
    printf("Enter window size:");
    scanf("%d",&window_size);
    for(int i=0;i<total_frames;++i)
    {
        window[i].frame_no = i;
        window[i].acked = 0;
    }
    while(sender_base<total_frames)
    {
        while(next_frame_to_send<sender_base+window_size && next_frame_to_send<total_frames)
        {
            if(window[next_frame_to_send].acked == 0)
            {
                send_frame(window[next_frame_to_send].frame_no);
            }
            next_frame_to_send++;
        }
        int recv;
        printf("Enter received frame number(or -1 if lost):");
        scanf("%d",&recv);
        if(recv>=0&&recv<total_frames&&window[recv].acked==0)
        {
            receive_frame(recv);
            send_ack(recv);
            window[recv].acked = 1;
        }
        printf("Enter ack number received by sender(-1 if none):");
        int ack_no;
        scanf("%d",&ack_no);
        if(ack_no>=0&&ack_no<total_frames&&window[ack_no].acked==1)
        {
            receive_frame(ack_no);
        }
        while(sender_base<total_frames && window[sender_base].acked==1)
        {
            sender_base++;
        }
    }
    printf("All frames are sent and acknowledged!");
    return 0;
}
