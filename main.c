#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

// --- ENUM VE UNION YAPILARI ---
typedef enum {
    TYPE_FLOAT32,
    TYPE_FLOAT16,
    TYPE_INT8
} TensorDataType;

typedef union {
    float *float32_data;
    uint16_t *float16_data;
    int8_t *int8_data;
} TensorData;

typedef struct {
    int rows;
    int cols;
    TensorDataType type;
    TensorData data;
} Tensor;

// --- TENSÖR OLUŞTURMA VE BELLEK YÖNETİMİ ---
Tensor* create_tensor(int rows, int cols, TensorDataType type) {
    Tensor *tensor = (Tensor *)malloc(sizeof(Tensor));
    if (tensor == NULL) return NULL;

    tensor->rows = rows;
    tensor->cols = cols;
    tensor->type = type;

    int total_elements = rows * cols;

    switch (type) {
        case TYPE_FLOAT32:
            tensor->data.float32_data = (float *)malloc(total_elements * sizeof(float));
            break;
        case TYPE_FLOAT16:
            tensor->data.float16_data = (uint16_t *)malloc(total_elements * sizeof(uint16_t));
            break;
        case TYPE_INT8:
            tensor->data.int8_data = (int8_t *)malloc(total_elements * sizeof(int8_t));
            break;
    }
    return tensor;
}

void free_tensor(Tensor *tensor) {
    if (tensor != NULL) {
        if (tensor->type == TYPE_FLOAT32) free(tensor->data.float32_data);
        else if (tensor->type == TYPE_FLOAT16) free(tensor->data.float16_data);
        else if (tensor->type == TYPE_INT8) free(tensor->data.int8_data);
        free(tensor);
    }
}

// --- VERİ DOLDURMA VE YAZDIRMA ---
void fill_tensor_random(Tensor *tensor) {
    int total_elements = tensor->rows * tensor->cols;
    for (int i = 0; i < total_elements; i++) {
        if (tensor->type == TYPE_FLOAT32) {
            tensor->data.float32_data[i] = (float)rand() / (float)(RAND_MAX) * 10.0f;
        } else if (tensor->type == TYPE_INT8) {
            tensor->data.int8_data[i] = (rand() % 256) - 128;
        }
    }
}

void print_tensor(Tensor *tensor) {
    printf("Tensor Boyutu: %dx%d | Tip: ", tensor->rows, tensor->cols);
    if (tensor->type == TYPE_FLOAT32) printf("FLOAT32\n");
    else if (tensor->type == TYPE_INT8) printf("INT8 (Quantized)\n");

    for (int r = 0; r < tensor->rows; r++) {
        for (int c = 0; c < tensor->cols; c++) {
            int index = (r * tensor->cols) + c;
            if (tensor->type == TYPE_FLOAT32) {
                printf("%8.3f ", tensor->data.float32_data[index]);
            } else if (tensor->type == TYPE_INT8) {
                printf("%4d ", tensor->data.int8_data[index]);
            }
        }
        printf("\n");
    }
    printf("-----------------------------------\n");
}

// --- QUANTIZATION (NİCEMLEME) FONKSİYONU ---
Tensor* quantize_tensor(Tensor *float_tensor) {
    if (float_tensor->type != TYPE_FLOAT32) return NULL;

    int total_elements = float_tensor->rows * float_tensor->cols;
    Tensor *quantized_tensor = create_tensor(float_tensor->rows, float_tensor->cols, TYPE_INT8);

    float max_abs = 0.0f;
    for (int i = 0; i < total_elements; i++) {
        float val = float_tensor->data.float32_data[i];
        if (val < 0) val = -val;
        if (val > max_abs) max_abs = val;
    }

    float scale = (max_abs == 0) ? 1.0f : (127.0f / max_abs);

    for (int i = 0; i < total_elements; i++) {
        float float_val = float_tensor->data.float32_data[i];
        quantized_tensor->data.int8_data[i] = (int8_t)(float_val * scale);
    }
    return quantized_tensor;
}

// --- ANA PROGRAM (MAIN) ---
int main() {
    srand(time(NULL));
    printf("--- TinyML Gomulu Sistem Tensor Demosu ---\n\n");

    Tensor *my_float_tensor = create_tensor(3, 3, TYPE_FLOAT32);
    fill_tensor_random(my_float_tensor);

    printf("1. Orijinal 32-Bit Float Tensor (Bellek: %d byte)\n", 9 * (int)sizeof(float));
    print_tensor(my_float_tensor);

    Tensor *my_quantized_tensor = quantize_tensor(my_float_tensor);

    printf("\n2. Quantize Edilmis 8-Bit Int Tensor (Bellek: %d byte)\n", 9 * (int)sizeof(int8_t));
    print_tensor(my_quantized_tensor);

    free_tensor(my_float_tensor);
    free_tensor(my_quantized_tensor);

    printf("\nIslem tamamlandi. Bellek basariyla temizlendi.\n");
    return 0;
}
