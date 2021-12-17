
/*Write the list of parsing error*/

 Parsing errors:
 * si il y a un delimiteur a la fin d'une commande (espaces compris) (ex : "cat >     ") ==> ✅
 * il ne doit pas y avoir plus de 2 caracteres sur un operateur (ex : "<<<" est une parsing error) => ✅
 * nombre impair de simple/double quotes ==> ✅
 * malloc size (if (ft_strlen(line) > SIZE_MAX) then error)
 * \ et ; ==> ✅
 

