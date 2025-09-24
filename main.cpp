#include <iostream>
#include <iomanip> // Libreria para manejar mejor la IO de la consola 

// Prototypes
int get_menu_option();
void consult_product();
void update_inventory();
void products_report();
void highest_price_product();

void print_index(int index);
int get_int_input(std::string prompt);
int get_index_by_code(int code);
int get_highest_price_product_index();
void wait_enter();

// Variables Globales
int elementCount = 6;
int codes[100] = {101, 102, 103, 104, 105, 106};
std::string names[100] = {"Martillo de bola", "Destornillador", "Cinta metrica", "Llave inglesa", "Taladro inalambrico", "Taladro"};
int stocks[100] = {10, 20, 30, 40, 50, 60};
float prices[100] = {105.99f, 68.99f, 40.00f, 50.00f, 499.99, 299.99f};

int main()
{
    bool is_program_running = true; // variable centinela

    while (is_program_running)
    {
        int opt = get_menu_option();
        switch (opt)
        {
        case 1: //
            consult_product();
            break;
        case 2:
            update_inventory();
            break;
        case 3:
            products_report();
            break;
        case 4:
            highest_price_product();
            break;
        case 5:
            std::cout << "Bye!" << std::endl;
            is_program_running = false;
            break;
        default:
            std::cout << "Esta opcion no existe. . ." << std::endl;
            break;
        }
        if (is_program_running)
            wait_enter();
    }
    return 0;
}

/**
 * Funcion para imprimir el menu y obtener una opción desde consola.
 * @return opción seleccionada
 */
int get_menu_option()
{
    // imprimir menu
    std::cout << "\n--- Menú principal ---" << std::endl;
    std::cout << "┌─────────────────────────────────────────┐" << std::endl;
    std::cout << "│ 1) Consultar un producto" << std::endl;
    std::cout << "│ 2) Actualizar inventario" << std::endl;
    std::cout << "│ 3) Generar reporte completo" << std::endl;
    std::cout << "│ 4) Encontrar el producto más caro" << std::endl;
    std::cout << "│ 5) Salir" << std::endl;
    std::cout << "└─────────────────────────────────────────┘" << std::endl;

    // obtener opcion desde input
    bool valid_input = false;
    int opt;

    // Validar opcion
    do
    {
        opt = get_int_input("Seleccione una opción [1-5]:");

        if (opt >= 1 && opt <= 5)
        {
            valid_input = true; // Si es una opcion valida salir
        }
        else
        {
            std::cout << "[Error] Debe ingresa una opción valida" << std::endl;
        }

    } while (!valid_input);
    return opt;
}

/**
 * Funcion para consultar un producto.
 */
void consult_product()
{
    std::cout << "\n--- Consulta de producto ---" << std::endl;
    std::cout << "Ingresa el codigo del producto a consultar" << std::endl;
    int code = get_int_input("codigo:");
    int index = get_index_by_code(code);

    if (index == -1) // si no se encontro producto
    {
        std::cout << "Producto con codigo no encontrado" << std::endl;
        return;
    }
    std::cout << "Informacion del producto:" << std::endl;
    print_index(index);
}

/**
 * Funcion para actualizar el inventario de un producto
 */
void update_inventory()
{
    std::cout << "\n--- Actualizar inventario ---" << std::endl;
    std::cout << "Ingresa el codigo del producto a actualizar" << std::endl;
    int code = get_int_input("codigo:");
    int index = get_index_by_code(code);

    if (index == -1) // si no se encontro producto
    {
        std::cout << "Producto con codigo no encontrado" << std::endl;
        return;
    }
    std::cout << "Producto: " << names[index] << " Stock actual: " << stocks[index] << std::endl;
    std::cout << "Ingresa la cantidad a incrementar o decrementar (Numero positivo o negativo)" << std::endl;
    int quantity = get_int_input("cantidad:");

    if (stocks[index] + quantity < 0) // si la cantidad queda en negativo
    {
        std::cout << "[Error] El numero despues del decremento no puede ser negativo." << std::endl;
        return;
    }
    stocks[index] += quantity;

    std::cout << "Se actualizo el stock a " << stocks[index] << std::endl;
}

/**
 * Funcion para imprimir en consolar todos los productos en un formato de tabla.
 */
void products_report()
{
    std::cout << "\n--- Reporte Completo ---" << std::endl;

    // Table Header
    std::cout << "┌───────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "|";
    std::cout << std::left << std::setw(10) << "Codigo" << "│";
    std::cout << std::left << std::setw(30) << "Nombre" << "│";
    std::cout << std::right << std::setw(10) << "Stock" << "│";
    std::cout << std::right << std::setw(10) << "Precio" << "│" << std::endl;

    // Table Middle
    std::cout << "├───────────────────────────────────────────────────────────────┤" << std::endl;

    for (int i = 0; i < elementCount; i++)
    {
        // Make Row
        std::cout << "|";
        std::cout << std::left << std::setw(10) << codes[i] << "|";
        std::cout << std::left << std::setw(30) << names[i] << "|";
        std::cout << std::right << std::setw(10) << stocks[i] << "|";
        std::cout << std::right << std::setw(1) << "$" << std::setw(9) << std::fixed << std::setprecision(2) << prices[i] << "|" << std::endl;
    }
    // Table footer
    std::cout << "└───────────────────────────────────────────────────────────────┘" << std::endl;

    std::cout << "--- Fin del Reporte ---" << std::endl;
}
/**
 * Funcion para imprimir en consola el producto mas caro.
 */
void highest_price_product()
{
    int index = get_highest_price_product_index();
    std::cout << "\n--- Producto mas caro ---" << std::endl;

    std::cout << "El producto más caro es: " << names[index] << " con un precio de " << prices[index] << std::endl;
}

/**
 * Función con validaciones para obtener un valor tipo int desde la consola.
 * @param prompt Breve mensaje antes de insertar el input
 * @return int numero ingresado desde consola.
 */
int get_int_input(std::string prompt)
{
    bool valid_input = false;
    int input;
    do
    {
        std::string temp;
        std::cout << prompt;
        std::getline(std::cin, temp);
        try
        {
            try
            {
                input = std::stoi(temp);
            }
            catch (std::out_of_range e) // validar rango de numero (rango -2,147,483,648 / 2,147,483,647)
            {
                std::cout << "[Error] Debe ingresar un número de menor tamaño" << std::endl;
                continue;
            }
        }
        catch (std::invalid_argument e) // Validar numeros
        {
            std::cout << "[Error] Debe ingresar un número" << std::endl;
            continue;
        }

        valid_input = true;
    } while (!valid_input);
    return input;
}

/**
 * Obtiene el indice de un producto a partir del codigo.
 *
 * @param code El codigo del producto
 * @return int el indice del producto.
 */
int get_index_by_code(int code)
{
    for (int i = 0; i < elementCount; i++)
    {
        if (code == codes[i])
        {
            return i;
        }
    }
    return -1;
}

/**
 * Regresa el indice del producto con el precio mas alto.
 * En caso de duplicidad se regresa el primer elemento.
 */
int get_highest_price_product_index()
{
    float price = prices[0];
    int index = 0;
    for (int i = 1; i < elementCount; i++)
    {
        if (price < prices[i])
        {
            price = prices[i];
            index = i;
        }
    }
    return index;
}

/**
 * Imprime en consola un producto a partir de su indice
 *
 * @param index indice del producto
 */
void print_index(int index)
{

    std::cout << "┌─────────────────────────────────────────┐" << std::endl;
    std::cout << "│ Codigo:" << codes[index] << std::endl;
    std::cout << "│ Nombre:" << names[index] << std::endl;
    std::cout << "│ Stock:" << stocks[index] << std::endl;
    std::cout << "│ Precio:" << prices[index] << std::endl;
    std::cout << "└─────────────────────────────────────────┘" << std::endl;
}


/**
 * Espera la entrada de una linea en la consola por parte del usuario
 */
void wait_enter()
{
    std::cout << "[Enter to continue . . .]";
    std::getchar();
}