# Explicación: Comportamiento de la Tabla de Símbolos en el Analizador Léxico

## Pregunta del Estudiante
¿Por qué en la tabla de símbolos solo aparecen identificadores y no las palabras reservadas, números o símbolos? ¿Por qué las palabras reservadas mal escritas (como "Entero", "RUTINA") aparecen como identificadores en lugar de errores?

## Respuesta Técnica

### 1. **Diseño Correcto de la Tabla de Símbolos**

La tabla de símbolos está implementada siguiendo las **convenciones estándar de compiladores**. Su propósito específico es almacenar únicamente **identificadores definidos por el usuario**, no todos los tokens del lenguaje.

### 2. **¿Qué contiene la Tabla de Símbolos?**

**✅ SÍ debe contener:**
- Identificadores válidos: `variable`, `contador`, `miFuncion`
- Identificadores que parecen palabras reservadas mal escritas: `Entero`, `RUTINA`, `sii`

**❌ NO debe contener:**
- **Palabras reservadas**: `entero`, `rutina`, `si` → Tienen tokens específicos (257-265)
- **Números**: `42`, `123` → Se almacenan como valores numéricos directamente
- **Símbolos**: `;`, `(`, `+` → Tienen códigos ASCII/tokens específicos
- **Cadenas**: `"Hola"` → Se almacenan en la tabla de cadenas separada

### 3. **Flujo del Analizador Léxico**

```
Input: "entero"  → Coincide exactamente → TOK_ENTERO (257) → NO va a tabla
Input: "Entero"  → No coincide → Regla {ID} → TOK_IDENTIFICADOR (266) → SÍ va a tabla
Input: "123"     → Regla {DIGITO}+ → TOK_NUMERO (267) → NO va a tabla
Input: ";"       → Regla específica → código ASCII (59) → NO va a tabla
```

### 4. **¿Por qué las palabras mal escritas son identificadores?**

Este es el **comportamiento correcto y esperado**:

- `"entero"` → Palabra reservada reconocida
- `"Entero"` → No coincide con ninguna palabra reservada → Se trata como identificador válido del usuario
- `"RUTINA"` → No coincide con `"rutina"` → Se trata como identificador válido del usuario

### 5. **Separación de Responsabilidades**

| Componente | Responsabilidad |
|------------|----------------|
| **Analizador Léxico** | Reconocer tokens y clasificarlos |
| **Tabla de Símbolos** | Almacenar identificadores del usuario |
| **Tabla de Cadenas** | Almacenar literales de cadena |
| **Analizador Sintáctico** | Validar que los identificadores estén bien usados |

### 6. **Ejemplo de Salida Esperada**

```
Entrada: entero miVar = 42; "Hola"; Entero;

Tabla de Símbolos:
| Índice | Nombre | Ntoken | Tipo |
|--------|--------|--------|------|
|   0    | miVar  |  266   |  0   |
|   1    | Entero |  266   |  0   |

Tabla de Cadenas:
| Índice | Cadena |
|--------|--------|
|   0    | Hola   |

Tokens generados:
- entero → TOK_ENTERO (257)
- miVar → TOK_IDENTIFICADOR (266), pos: 0
- = → TOK_ASIGNACION (61)
- 42 → TOK_NUMERO (267), valor: 42
- ; → TOK_PUNTO_Y_COMA (59)
- "Hola" → TOK_CADENA (268), pos: 0
- ; → TOK_PUNTO_Y_COMA (59)
- Entero → TOK_IDENTIFICADOR (266), pos: 1
```

### 7. **Conclusión**

El comportamiento observado es **técnicamente correcto** y sigue las mejores prácticas de diseño de compiladores. La tabla de símbolos cumple su función específica de almacenar únicamente los identificadores que el usuario define en su código fuente.

### 8. **Opciones de Mejora (Opcional)**

Si se quisiera detectar palabras reservadas mal escritas como errores, se podría:

1. **Opción A**: Agregar reglas específicas en Flex para detectarlas como errores
2. **Opción B**: Implementar una fase de post-procesamiento que analice los identificadores
3. **Opción C**: Mantener el comportamiento actual (recomendado por estándares)

---

**Implementado por:** [Tu nombre]  
**Fecha:** 12 de julio de 2025  
**Curso:** Compiladores
