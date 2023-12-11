#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcs.hpp"
#include "matmul.hpp"

int n = 256;
int d = 256;
float* input; // (256,1)
char* weights; // (256,256)
float* output; // (256,1)
float expectedOutputF32[256] = {
    0.00940421689, 0.0099773258, 0.00998678058, 0.00987196993, 0.0104839709, 0.00963028241, 0.0103303399, 0.0105523383, 
    0.00993812457, 0.0096816523, 0.00982786808, 0.0100828549, 0.0105102677, 0.00949237496, 0.0103284307, 0.00956133474, 
    0.00998091977, 0.0101781245, 0.0098706698, 0.00995308254, 0.00990086515, 0.010440927, 0.00928415731, 0.0101713268, 
    0.0101519162, 0.0108743943, 0.00967309065, 0.00994043425, 0.010914553, 0.0100540509, 0.00992546976, 0.00919564068, 
    0.0100085856, 0.00948840007, 0.00984928012, 0.0097392993, 0.00943168066, 0.010371333, 0.0100491699, 0.0100159543, 
    0.00951363891, 0.00903787557, 0.00986593589, 0.00978378579, 0.00995478593, 0.00992373098, 0.0101374956, 0.00975185074, 
    0.0102556925, 0.0106861293, 0.0107260346, 0.00985367596, 0.0101121403, 0.0105792377, 0.0100910356, 0.0100313127, 
    0.00992171466, 0.0101274289, 0.00962551683, 0.00988054462, 0.00998489652, 0.0102490345, 0.0105652111, 0.00979148131, 
    0.00986643322, 0.0097002862, 0.00974584091, 0.0100425268, 0.0101309139, 0.0103045134, 0.00935478415, 0.00934733357, 
    0.00983540714, 0.0100984368, 0.00981204305, 0.00955333468, 0.0098296497, 0.0101149827, 0.0104352906, 0.0100277141, 
    0.00974422321, 0.00986846723, 0.0106688505, 0.00985412113, 0.0101528624, 0.0103138955, 0.0105053112, 0.00977999996, 
    0.0101912441, 0.00940482877, 0.0092552295, 0.0101204636, 0.0101984702, 0.0102462256, 0.0101562943, 0.00978875998, 
    0.00918525271, 0.00957012735, 0.00930453092, 0.010339126, 0.00995809305, 0.00943322573, 0.010251943, 0.00994762685, 
    0.0097962087, 0.0100758569, 0.010072019, 0.0102713723, 0.00987767521, 0.00984509755, 0.0105618685, 0.00934103131, 
    0.00955452677, 0.00898624118, 0.00928340573, 0.0100816153, 0.00961570442, 0.00984057598, 0.00942536537, 0.0104031106, 
    0.00921231508, 0.0099330591, 0.0102412738, 0.0103561794, 0.00963713415, 0.0101908082, 0.00952064339, 0.00988186523, 
    0.0101244068, 0.0100983921, 0.00984164793, 0.00980425347, 0.0100872014, 0.0103063248, 0.00951577909, 0.00982981175, 
    0.0104034469, 0.0105332863, 0.00933259074, 0.0102054048, 0.0103698708, 0.0103398552, 0.0103476876, 0.010120837, 
    0.00941165723, 0.0102630295, 0.0103325732, 0.0088344356, 0.00996787753, 0.0103692189, 0.0100811748, 0.0102394251, 
    0.00963100605, 0.0097583821, 0.0102346269, 0.00942486338, 0.00963231176, 0.00947069656, 0.0100238035, 0.00998976827, 
    0.0104776835, 0.00912889186, 0.0104263797, 0.00966134761, 0.00979522616, 0.0102813542, 0.00989940483, 0.0106002018, 
    0.00944493432, 0.00986790843, 0.0104004405, 0.010639986, 0.00991946738, 0.00982504711, 0.0097590629, 0.00934090838, 
    0.00941457506, 0.0105609912, 0.0098660076, 0.0102888672, 0.00975077879, 0.0096084075, 0.0102644283, 0.010095383, 
    0.00999560393, 0.00971658621, 0.0106628025, 0.0100364666, 0.00959276222, 0.00964209437, 0.00996889733, 0.0101592569, 
    0.00916973222, 0.00989935361, 0.00963595696, 0.00919423811, 0.00938981585, 0.0101490337, 0.0101000667, 0.0101436758, 
    0.0101261875, 0.0102992589, 0.00940008927, 0.010087396, 0.0093733659, 0.00985787902, 0.00947509147, 0.0109101618, 
    0.00976323802, 0.0102105886, 0.00979421288, 0.00985157397, 0.00939049013, 0.00912318751, 0.00966591947, 0.0100339837, 
    0.0096283108, 0.00976636633, 0.0101569109, 0.00983331073, 0.0106756007, 0.00984195527, 0.00969533902, 0.00979026128, 
    0.00994522031, 0.0104742656, 0.00986961834, 0.00919381902, 0.0103511643, 0.00936353672, 0.00885079522, 0.0099128047, 
    0.00999643374, 0.00967285875, 0.00944127701, 0.0101960786, 0.0100323027, 0.0102470927, 0.0101006664, 0.00979286898, 
    0.00983102713, 0.00982029364, 0.00956993457, 0.00980226975, 0.00953686144, 0.00983348489, 0.0105020618, 0.00999733713, 
    0.00984117482, 0.010183882, 0.00954863429, 0.00999936648, 0.00985846296, 0.0102046141, 0.00948831439, 0.00990356226,
};

void compareOrFail(const char *name, float* o, float* eo, int size) {
    int ix = -1;
    for (int i = 0; i < size; i++) {
        if (o[i] != eo[i]) {
            ix = i;
            break;
        }
    }
    if (ix < 0) {
        printf("[%s] ✅\n", name);
    } else {
        printf("[%s] ❌ ix=%d\n", name, ix);
        printf("%.9g != %.9g\n", o[ix], eo[ix]);
        exit(-1);
    }
}

void test_f32() {
    matmul(F32, output, input, weights, n, d);
    compareOrFail("f32", output, expectedOutputF32, d);
}

void test_f32_sliced() {
    int slices = 8;

    MatMulSlice* slice = new MatMulSlice(F32, slices, n, d);

    for (int s = 0; s < slices; s++) {
        char* weights0 = new char[slice->weights0Bytes];

        long weightsOffset = slice->splitWeights(s, weights, weights0);

        float* output0 = new float[slice->d0];
        matmul(F32, output0, input, weights0, slice->n, slice->d0);

        long outputOffset = slice->mergeOutputs(s, output, output0);

        delete[] weights0;
        delete[] output0;

        printf("weights <%8ld, %8ld> output <%4ld, %4ld>\n",
            weightsOffset,
            weightsOffset + slice->weights0Bytes,
            outputOffset,
            outputOffset + slice->d0);
    }

    delete slice;
    compareOrFail("f32_sliced", output, expectedOutputF32, d);
}

void test_dequantizeQ40Row() {
    uint8_t data[] = {
        0x33, 0x2f, 0xa9, 0xcb, 0xdc, 0xfe, 0x80, 0xa9, 0xcb, 0xdc, 0xfe, 0x80, 0xa9, 0xcb, 0xdc, 0xfe, 0x80, 0xa9,
        0x33, 0xaf, 0x67, 0x45, 0x34, 0x12, 0x80, 0x67, 0x45, 0x34, 0x12, 0x80, 0x67, 0x45, 0x34, 0x12, 0x80, 0x67,
    };
    float row[64];
    dequantizeQ40Row((BlockQ40*)&data, row, 64);

    float expectedRow[] = {
        0.112487793, 0.224975586, 0.337463379, 0.449951172, 0.449951172, 0.562438965, 0.674926758, 0.787414551, -0.899902344, 0,
        0.112487793, 0.224975586, 0.337463379, 0.449951172, 0.449951172, 0.562438965, 0.674926758, 0.787414551, -0.899902344, 0,
        0.112487793, 0.224975586, 0.337463379, 0.449951172, 0.449951172, 0.562438965, 0.674926758, 0.787414551, -0.899902344, 0,
        0.112487793, 0.224975586, 0.112487793, 0.224975586, 0.337463379, 0.449951172, 0.449951172, 0.562438965, 0.674926758, 0.787414551, 0.899902344, -0,
        0.112487793, 0.224975586, 0.337463379, 0.449951172, 0.449951172, 0.562438965, 0.674926758, 0.787414551, 0.899902344, -0,
        0.112487793, 0.224975586, 0.337463379, 0.449951172, 0.449951172, 0.562438965, 0.674926758, 0.787414551, 0.899902344, -0, 0.112487793, 0.224975586
    };

    compareOrFail("dequantizeQ40Row", row, expectedRow, 64);
}

int main() {
    initQuants();

    input = new float[n];
    weights = new char[n * d * sizeof(float)];
    output = new float[d];

    unsigned long long state = 800000010L;
    int i;
    for (i = 0; i < n; i++) input[i] = randomF32(&state) / 80.0;
    for (i = 0; i < n * d; i++) ((float*)weights)[i] = randomF32(&state) / 80.0;

    memset(output, 0, d * sizeof(float));
    test_f32();

    memset(output, 0, d * sizeof(float));
    test_f32_sliced();

    test_dequantizeQ40Row();

    delete[] input;
    delete[] weights;
    delete[] output;
    return 0;
}
