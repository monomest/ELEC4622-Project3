/*****************************************************************************/
// File: main4.cpp
// Author: David Taubman & Renee Lu
// Last Revised: 4 August, 2020
/*****************************************************************************/
// Copyright 2007, David Taubman, The University of New South Wales (UNSW)
/*****************************************************************************/

#include "io_bmp.h"
#include "image_comps.h"
#include <math.h>
#include <tuple>
#include <vector>
#include <iostream> 
#include <cstdlib>
#include <time.h>
#include <algorithm>

using namespace std;

/* ========================================================================= */
/*                 IMPLEMENTATION OF 'my_image_comp' FUNCTIONS               */
/* ========================================================================= */

/*---------------------------------------------------------------------------*/
/*                  my_image_comp::perform_boundary_extension                */
/*                         Odd Symmetric Extension                           */
/*---------------------------------------------------------------------------*/

void my_image_comp::perform_boundary_extension()
{
    int r, c;

    // First extend upwards by border
    float* first_line = buf;
    for (r = 1; r <= border; r++)
        for (c = 0; c < width; c++)
            first_line[-r * stride + c] = first_line[r * stride + c];

    // Now extend downwards by border
    float* last_line = buf + (height - 1) * stride;
    for (r = 1; r <= border; r++)
        for (c = 0; c < width; c++)
            last_line[r * stride + c] = last_line[-r * stride + c];

    // Now extend all rows to the left and to the right
    float* left_edge = buf - border * stride;
    float* right_edge = left_edge + width - 1;
    for (r = height + 2 * border; r > 0; r--, left_edge += stride, right_edge += stride)
        for (c = 1; c <= border; c++)
        {
            left_edge[-c] = left_edge[c];
            right_edge[c] = right_edge[-c];
        }
}

/*---------------------------------------------------------------------------*/
/*                     my_image_comp::perform_zero_padding                   */
/*                         Odd Symmetric Extension                           */
/*---------------------------------------------------------------------------*/

void my_image_comp::perform_zero_padding()
{
    int r, c;

    // First extend upwards by border
    float* first_line = buf;
    for (r = 1; r <= border; r++)
        for (c = 0; c < width; c++)
            first_line[-r * stride + c] = 0;

    // Now extend downwards by border
    float* last_line = buf + (height - 1) * stride;
    for (r = 1; r <= border; r++)
        for (c = 0; c < width; c++)
            last_line[r * stride + c] = 0;

    // Now extend all rows to the left and to the right
    float* left_edge = buf - border * stride;
    float* right_edge = left_edge + width - 1;
    for (r = height + 2 * border; r > 0; r--, left_edge += stride, right_edge += stride)
        for (c = 1; c <= border; c++)
        {
            left_edge[-c] = 0;
            right_edge[c] = 0;
        }
}

/* ========================================================================= */
/*                              Global Functions                             */
/* ========================================================================= */

/*---------------------------------------------------------------------------*/
/*                               perform_erosion                             */
/*---------------------------------------------------------------------------*/

void perform_erosion(my_image_comp* in, my_image_comp* out,
    vector<int>& A_off, int N, int debug)
{
    // Perform the erosion
    for (int n1 = 0; n1 < out->height; n1++)
        for (int n2 = 0; n2 < out->width; n2++)
        {
            float* p_n = in->buf + n1 * in->stride + n2;
            float* op = out->buf + n1 * out->stride + n2;
            int val = 255;
            for (int i = 0; i < N; i++)
            {
                val &= int(p_n[A_off.at(i)]);
            }
            *op = val;
        }
}

/*---------------------------------------------------------------------------*/
/*                                    main                                   */
/*---------------------------------------------------------------------------*/

int
main(int argc, char* argv[])
{
    /* Start the timer */
    clock_t time = clock();
    int debug = 0;
    bool zero_pad = false;

    /* Get the args */
    if (argc != 5)
    {
        fprintf(stderr, "Usage: %s <input bmp file> <output bmp file> <radius r> [zero pad = 1 or 0]\n", argv[0]);
        return -1;
    }
    int zero_arg = atoi(argv[4]);
    if (zero_arg == 1)
        zero_pad = true;
    else
        zero_pad = false;
    int r = abs(atoi(argv[3]));         // Get the absolute value of the radius
    int r_lim = (r + 0.5) * (r + 0.5);  // (r+0.5)^2

    /* Brute Force for Circular Structuring Set A */
    // Represent structuring set A by 2D vector of size N x M 
    // Create A containing N vectors of size M
    // A = < < a1[0], a2[0] >         ^
    //       < a1[1], a2[1] >         |
    //       < a1[2], a2[2] >         N
    //              ...               |
    //       < a1[N-1], a2[N-1]> >    v
    // <------------- M -------------->
    // Structuring Set A
    vector<vector<int>> A;
    // When radius is zero only a single 
    // point will be printed 
    if (r == 0)
        A.push_back({ 0, 0 });
    else
    {
        for (int y = -r; y <= r; y++)
            for (int x = -r; x <= r; x++)
            {
                if (x * x + y * y < r_lim)
                    A.push_back({ x, y });
            }
    }

    /* Determine the border and A dimensions */
    // Border is radius
    int border = r;
    int N = A.size();   // N x M vector A   
    // Debugging circle set
    if (debug)
    {
        printf("------Debugging circle structuring set------\n");
        for (int i = 0; i < N; i++)
        {
            printf("%d %d\n", A[i][0], A[i][1]);
        }
        printf("N = %d\n", N);
    }

    /* Create the input image storage */
    int err_code = 0;
    try {
        // Read the input image
        bmp_in in;
        if ((err_code = bmp_in__open(&in, argv[1])) != 0)
            throw err_code;
        // Get input and input border dimensions
        int width = in.cols, height = in.rows;
        int n, num_comps = in.num_components;   // Number of colour components
        // Initialise the input storage
        my_image_comp* input_comps = new my_image_comp[num_comps];
        for (n = 0; n < num_comps; n++)
            input_comps[n].init(height, width, border); // Leave a border

        int r; // Declare row index
        io_byte* line = new io_byte[width * num_comps];
        for (r = height - 1; r >= 0; r--)
        { // "r" holds the true row index we are reading, since the image is
          // stored upside down in the BMP file.
            if ((err_code = bmp_in__get_line(&in, line)) != 0)
                throw err_code;
            for (n = 0; n < num_comps; n++)
            {
                io_byte* src = line + n; // Points to first sample of component n
                float* dst = input_comps[n].buf + r * input_comps[n].stride;
                for (int c = 0; c < width; c++, src += num_comps)
                    dst[c] = (float)*src; // The cast to type "float" is not
                          // strictly required here, since bytes can always be
                          // converted to floats without any loss of information.
            }
        }
        bmp_in__close(&in);

        /*------------------------------- TASK 4 -------------------------------*/

        // Symmetric extension for input
        if (zero_pad)
        {
            for (n = 0; n < num_comps; n++)
                input_comps[n].perform_zero_padding();
        }
        else
        {
            for (n = 0; n < num_comps; n++)
                input_comps[n].perform_boundary_extension();
        }

        // Allocate storage for the filtered output
        my_image_comp* output_comps = new my_image_comp[num_comps];
        for (n = 0; n < num_comps; n++)
        {
            output_comps[n].init(height, width, 0);
        }

        // Create sorted 1D vector A_off of size N
        // A_off = < a_off[0], a_off[1], ... , a_off[N-1] >
        //        <------------------ N ------------------->
        vector<int> A_off;
        int S = input_comps[0].stride;  // Stride
        for (int row = 0; row < N; row++)
        {
            int a_off = A[row][0] * S + A[row][1];
            A_off.push_back(a_off);
        }
        sort(A_off.begin(), A_off.end());
        if (debug)
        {
            printf("------Debugging A_off------\n");
            for (int i = 0; i < A_off.size(); i++)
            {
                printf("%d ", A_off[i]);
            }
            printf("\n");
        }

        // Process the image, all in floating point (easy)
        for (n = 0; n < num_comps; n++)
            perform_erosion(input_comps + n, output_comps + n, A_off, N, debug);

        /*-------------------------------------------------------------------------*/

       // Write the image back out again
        bmp_out out;
        if ((err_code = bmp_out__open(&out, argv[2], width, height, num_comps)) != 0)
            throw err_code;
        for (r = height - 1; r >= 0; r--)
        { // "r" holds the true row index we are writing, since the image is
          // written upside down in BMP files.
            for (n = 0; n < num_comps; n++)
            {
                io_byte* dst = line + n; // Points to first sample of component n
                float* src = output_comps[n].buf + r * output_comps[n].stride;
                for (int c = 0; c < width; c++, dst += num_comps)
                {
                    // Deal with overflow and underflow
                    if (src[c] > 255)
                        src[c] = 255;
                    else if (src[c] < 0)
                        src[c] = 0;
                    // Write output to destination
                    *dst = (io_byte)src[c];
                }
            }
            bmp_out__put_line(&out, line);
        }
        bmp_out__close(&out);
        delete[] line;
        delete[] input_comps;
        delete[] output_comps;
    }
    catch (int exc) {
        if (exc == IO_ERR_NO_FILE)
            fprintf(stderr, "Cannot open supplied input or output file.\n");
        else if (exc == IO_ERR_FILE_HEADER)
            fprintf(stderr, "Error encountered while parsing BMP file header.\n");
        else if (exc == IO_ERR_UNSUPPORTED)
            fprintf(stderr, "Input uses an unsupported BMP file format.\n  Current "
                "simple example supports only 8-bit and 24-bit data.\n");
        else if (exc == IO_ERR_FILE_TRUNC)
            fprintf(stderr, "Input or output file truncated unexpectedly.\n");
        else if (exc == IO_ERR_FILE_NOT_OPEN)
            fprintf(stderr, "Trying to access a file which is not open!(?)\n");
        return -1;
    }
    /* End the timer */
    time = clock() - time;
    printf("This program took %f seconds.\n", ((float)time) / CLOCKS_PER_SEC);
    return 0;
}