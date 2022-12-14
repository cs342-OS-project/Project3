#ifndef FRAME_TABLE
#define FRAME_TABLE

#define EXISTS '1'
#define EMPTY '0'

// Definitions

struct frame_table_entry
{
    char available;
    int LRU_count;
    int page_number1;
    int page_number2;
};

struct frame_table_entry *init_frame_table(int size);

void free_frame_table(struct frame_table_entry *frame_table);

int available_frame(struct frame_table_entry *frame_table, int size);

int LRU_frame(struct frame_table_entry *frame_table, int size);

void update_LRU(struct frame_table_entry *frame_table, int size, int index);

void print_LRU_counts(struct frame_table_entry *frame_table, int size);

// Implementation

struct frame_table_entry *init_frame_table(int size)
{
    struct frame_table_entry *frame_table = malloc(sizeof(struct frame_table_entry) * size);

    for (int i = 0; i < size; i++)
    {
        frame_table[i].available = EMPTY;
        frame_table[i].LRU_count = 0;
    }
    return frame_table;
}

void free_frame_table(struct frame_table_entry *frame_table)
{
    free(frame_table);
}

int available_frame(struct frame_table_entry *frame_table, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (frame_table[i].available == EMPTY)
        {
            return i;
        }
    }
    return -1;
}

int LRU_frame(struct frame_table_entry *frame_table, int size)
{
    int maxIndex = 0;

    for (int i = 0; i < size; i++)
    {
        if ( frame_table[maxIndex].LRU_count < frame_table[i].LRU_count )
        {
            maxIndex = i;
        }
    }
    return maxIndex;
}

void update_LRU(struct frame_table_entry *frame_table, int size, int index)
{
    frame_table[index].LRU_count = 0;
    
    for (int i = 0; i < size; i++)
    {
        if ( i != index && frame_table[i].available == EXISTS )
        {
            frame_table[i].LRU_count++;
        }
    }
}

void print_LRU_counts(struct frame_table_entry *frame_table, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d -> %d ", i, frame_table[i].LRU_count);
    }
    printf("\n");
}

#endif