
archivos = "paquetes1.txt"

paquetes ={
    1:{"destino":"Viaje a cancun con un hotel todo incluido","precio":2300},
    2:{"destino":"Viaje a Machu Pichu con guia turistico","precio":1450},
    3:{"destino":"Viaje a cancun con un hotel todo incluido","precio":2800},
}

def login ():
    while True:
        usCorr = "User" 
        contCorr = "123"
        print("=== LOGING ===")
        usuario = input("Ingrese el usuario: ")
        contraseña = input("Ingrese el usuario: ")
        if usCorr == usuario and contraseña ==contCorr:
            print("Inicio de secion exitoso")
            break
        else:
            print("Credenciales incorrectas")
        

def rergistrarPaquete():
    cliente = input("Ingrese su nombre: ")
    print("Seleccione un paquete:")
    for k, v in paquetes.items():
        print(f"{k}. {v['destino']} - ${v['precio']}")
    try:
        opcion = int(input("Ingresa una opcion: "))
    except ValueError:
        print("Opcion invalida")
        return

    if opcion not in paquetes:
        print("Opcion invalida")
        return
    precio = paquetes[opcion]['precio']
    codigo = f"R{opcion}{precio}"
    reserva = {
        "Codigo": codigo,
        "Cliente": cliente,
        "Destino": paquetes[opcion]['destino'],
        "Precio": precio
    }
    with open(archivos, "a") as file:
        file.write(str(reserva) + "\n")
    print("La reserva se ha registrado correctamente")
    print(f"Codigo de la reserva: {codigo}\n")

def actualizar_reserva():
    try:
        with open(archivos, "r") as file:
            reservas = file.readlines()

        if not reservas:
            print("No existen reservas registradas\n")
            return

        codigo = input("Ingrese el codigo de la reserva a actualizar: ")
        encontrada = False
        nuevas_reservas = []

        for r in reservas:
            reserva = eval(r)
            if reserva["codigo"] == codigo:
                encontrada = True
                print("Seleccione un nuevo paquete:")
                for k, v in paquetes.items():
                    print(f"{k}. {v['destino']} - ${v['precio']}")

                opcion = int(input("Nueva opcion: "))
                if opcion not in paquetes:
                    print("Opcion invalida")
                    return

                precio = paquetes[opcion]['precio']
                reserva["Destino"] = paquetes[opcion]['destino']
                reserva["Precio"] = precio
                reserva["codigo"] = f"R{opcion}{precio}"

            nuevas_reservas.append(reserva)

        if not encontrada:
            print("Codigo no encontrado\n")
            return

        with open(archivos, "w") as file:
            for r in nuevas_reservas:
                file.write(str(r) + "\n")

        print("Reserva actualizada correctamente\n")

    except FileNotFoundError:
        print("No existen reservas registradas\n")


def eliminar_reserva():
    try:
        with open(archivos, "r") as file:
            reservas = file.readlines()

        if not reservas:
            print("No existen reservas registradas\n")
            return

        codigo = input("Ingrese el codigo de la reserva a eliminar: ")
        nuevas_reservas = []
        eliminada = False

        for r in reservas:
            reserva = eval(r)
            if reserva["codigo"] == codigo:
                eliminada = True
                continue
            nuevas_reservas.append(reserva)

        if not eliminada:
            print("Codigo no encontrado\n")
            return

        with open(archivos, "w") as file:
            for r in nuevas_reservas:
                file.write(str(r) + "\n")

        print("Reserva eliminada correctamente\n")

    except FileNotFoundError:
        print("No existen reservas registradas\n")


def menu():
    login()
    while True:
        print("\n Menu ")
        print("1. Registrar paquetes")
        print("2. Ver todos los paquete")
        print("3. Consular un paquete por codigo")
        print("4. Salir del sistema")
        try:
            opcion = int(input("Ingrese la opcion: "))
            if opcion == 1:
                print("Registrar paquetes")
                rergistrarPaquete()
            elif opcion == 2:
                print("Ver todos los paquetes")
                
            elif opcion == 3:
                print("Consular un paquete por codigo")
                
            elif opcion == 4:
                print("Saliendo ")
                break
            else:
                print("Por favor ingrese una opcion valida")
        except ValueError:
            print("Opciom invalida")
menu()