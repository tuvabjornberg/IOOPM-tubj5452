**STRUKTUR**
Rätt namngivet, strukturerat, lättläst. Lagom stora mellanrum. 

- ioopm_hash_table_has key är bunden till att key är en int eftersom att key_equiv förutsätter att inputen är en int. 
- Liknande med ioopm_hash_table_has_value som tar den statsika funktionen value_quiv som förutsätter att value är en sträng. 
- För att göra den mer allmänn skulle has_key och has_value ta in en compare funktion. d

- #define ioopm_predicate och ioopm_apply_function kan ligga i h-filen

- .p är svårtolkat, något med void kanske är bättre, har .integer, .string annars som är tydligt vad elementet ska vara. 

- Från rad 340-388 är död kod, funktioner som varken används inom ht eller är satta i h-filen för andra funktioner ska komma åt dessa. 

- Ingen upprepande kod som skulle kunna extarheras på något vettiggt sätt. 

- No_Buckets istället för 17 = bra!

- Inga klasser/metoder som är för omfatatnde/komplicerande

**VARIABLER**
- Blandar cursor och entry, kan vara svårt att förstå vad cursor är för något. 

- Annars är variablerna namngivna och initerade vettiga. 

- Vi hittar inga redundanta variabler.

**LOOPAR OCH VILLKORSSATSER**
- Rätt strukturerade men okonsekventa gällande placering av måsvingar, mellanrum och nya rader. 

- if(keys == NULL){} else, inget sker när keys är NULL, bättre att sätta if (keys != NULL) {for ...}  ex. rad 234, vanligaste caset är i else
- Blandat om vanligaste fallen först i if else. 

- Inga case satser. 

- for-looparna har oftast No_Buckets, vilket är en uppenålig int som ht även initieras med. while går alltid till ett vettigt slut

- for-looparna rätt, while är en del av strukten dvs rätt initierade. 

- Finns inga uttryck/satser som kan brytas ut. 

**DEFFENSIV PROGRAMMERING**
- Minne verkar städas rätt och på rätt ställe. 

- Gränsvärden testas (ex tomma ht). 

- Har asserts för invalid data. 

- Ht öppnar inga filer. 
