#pragma once

template <unsigned int SIZE>
class Buffer
{
private:
    float array[SIZE];
    int idx = 0;

public:
    Buffer() = default;
    void add(float val)
    {
        array[idx++ % SIZE] = val;
    }
    float getAverage()
    {
        float sum = 0;
        for (int i = 0; i < SIZE; i++)
        {
            sum += array[i];
        }
        return (sum) / ((float)(SIZE));
    }
    float getSD()
    {
        float sum = 0;
        float avg = getAverage;
        for (int i = 0; i < SIZE; i++)
        {
            sum += pow((array[i] - avg), 2.0);
        }
        return sqrt(sum / (SIZE - 1.0));
    }
};
