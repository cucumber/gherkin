#include <cucumber/gherkin/dialect.hpp>

namespace cucumber::gherkin {

const keywords_maps&
all_keywords()
{
    static const keywords_maps kwms = {
    {
        "af",
        {
            { "and", { "* ", "En " } },
            { "background", { "Agtergrond" } },
            { "but", { "* ", "Maar " } },
            { "examples", { "Voorbeelde" } },
            { "feature", { "Funksie", "Besigheid Behoefte", "Vermoë" } },
            { "given", { "* ", "Gegewe " } },
            { "rule", { "Regel" } },
            { "scenario", { "Voorbeeld", "Situasie" } },
            { "scenarioOutline", { "Situasie Uiteensetting" } },
            { "then", { "* ", "Dan " } },
            { "when", { "* ", "Wanneer " } }
        }
    },
    {
        "am",
        {
            { "and", { "* ", "Եվ " } },
            { "background", { "Կոնտեքստ" } },
            { "but", { "* ", "Բայց " } },
            { "examples", { "Օրինակներ" } },
            { "feature", { "Ֆունկցիոնալություն", "Հատկություն" } },
            { "given", { "* ", "Դիցուք " } },
            { "rule", { "Rule" } },
            { "scenario", { "Օրինակ", "Սցենար" } },
            { "scenarioOutline", { "Սցենարի կառուցվացքը" } },
            { "then", { "* ", "Ապա " } },
            { "when", { "* ", "Եթե ", "Երբ " } }
        }
    },
    {
        "an",
        {
            { "and", { "* ", "Y ", "E " } },
            { "background", { "Antecedents" } },
            { "but", { "* ", "Pero " } },
            { "examples", { "Eixemplos" } },
            { "feature", { "Caracteristica" } },
            { "given", { "* ", "Dau ", "Dada ", "Daus ", "Dadas " } },
            { "rule", { "Rule" } },
            { "scenario", { "Eixemplo", "Caso" } },
            { "scenarioOutline", { "Esquema del caso" } },
            { "then", { "* ", "Alavez ", "Allora ", "Antonces " } },
            { "when", { "* ", "Cuan " } }
        }
    },
    {
        "ar",
        {
            { "and", { "* ", "و " } },
            { "background", { "الخلفية" } },
            { "but", { "* ", "لكن " } },
            { "examples", { "امثلة" } },
            { "feature", { "خاصية" } },
            { "given", { "* ", "بفرض " } },
            { "rule", { "Rule" } },
            { "scenario", { "مثال", "سيناريو" } },
            { "scenarioOutline", { "سيناريو مخطط" } },
            { "then", { "* ", "اذاً ", "ثم " } },
            { "when", { "* ", "متى ", "عندما " } }
        }
    },
    {
        "ast",
        {
            { "and", { "* ", "Y ", "Ya " } },
            { "background", { "Antecedentes" } },
            { "but", { "* ", "Peru " } },
            { "examples", { "Exemplos" } },
            { "feature", { "Carauterística" } },
            { "given", { "* ", "Dáu ", "Dada ", "Daos ", "Daes " } },
            { "rule", { "Rule" } },
            { "scenario", { "Exemplo", "Casu" } },
            { "scenarioOutline", { "Esbozu del casu" } },
            { "then", { "* ", "Entós " } },
            { "when", { "* ", "Cuando " } }
        }
    },
    {
        "az",
        {
            { "and", { "* ", "Və ", "Həm " } },
            { "background", { "Keçmiş", "Kontekst" } },
            { "but", { "* ", "Amma ", "Ancaq " } },
            { "examples", { "Nümunələr" } },
            { "feature", { "Özəllik" } },
            { "given", { "* ", "Tutaq ki ", "Verilir " } },
            { "rule", { "Rule" } },
            { "scenario", { "Nümunə", "Ssenari" } },
            { "scenarioOutline", { "Ssenarinin strukturu" } },
            { "then", { "* ", "O halda " } },
            { "when", { "* ", "Əgər ", "Nə vaxt ki " } }
        }
    },
    {
        "be",
        {
            { "and", { "* ", "I ", "Ды ", "Таксама " } },
            { "background", { "Кантэкст" } },
            { "but", { "* ", "Але ", "Інакш " } },
            { "examples", { "Прыклады" } },
            { "feature", { "Функцыянальнасць", "Фіча" } },
            { "given", { "* ", "Няхай ", "Дадзена " } },
            { "rule", { "Правілы" } },
            { "scenario", { "Сцэнарый", "Cцэнар" } },
            { "scenarioOutline", { "Шаблон сцэнарыя", "Узор сцэнара" } },
            { "then", { "* ", "Тады " } },
            { "when", { "* ", "Калі " } }
        }
    },
    {
        "bg",
        {
            { "and", { "* ", "И " } },
            { "background", { "Предистория" } },
            { "but", { "* ", "Но " } },
            { "examples", { "Примери" } },
            { "feature", { "Функционалност" } },
            { "given", { "* ", "Дадено " } },
            { "rule", { "Правило" } },
            { "scenario", { "Пример", "Сценарий" } },
            { "scenarioOutline", { "Рамка на сценарий" } },
            { "then", { "* ", "То " } },
            { "when", { "* ", "Когато " } }
        }
    },
    {
        "bm",
        {
            { "and", { "* ", "Dan " } },
            { "background", { "Latar Belakang" } },
            { "but", { "* ", "Tetapi ", "Tapi " } },
            { "examples", { "Contoh" } },
            { "feature", { "Fungsi" } },
            { "given", { "* ", "Diberi ", "Bagi " } },
            { "rule", { "Rule" } },
            { "scenario", { "Senario", "Situasi", "Keadaan" } },
            { "scenarioOutline", { "Kerangka Senario", "Kerangka Situasi", "Kerangka Keadaan", "Garis Panduan Senario" } },
            { "then", { "* ", "Maka ", "Kemudian " } },
            { "when", { "* ", "Apabila " } }
        }
    },
    {
        "bs",
        {
            { "and", { "* ", "I ", "A " } },
            { "background", { "Pozadina" } },
            { "but", { "* ", "Ali " } },
            { "examples", { "Primjeri" } },
            { "feature", { "Karakteristika" } },
            { "given", { "* ", "Dato " } },
            { "rule", { "Rule" } },
            { "scenario", { "Primjer", "Scenariju", "Scenario" } },
            { "scenarioOutline", { "Scenariju-obris", "Scenario-outline" } },
            { "then", { "* ", "Zatim " } },
            { "when", { "* ", "Kada " } }
        }
    },
    {
        "ca",
        {
            { "and", { "* ", "I " } },
            { "background", { "Rerefons", "Antecedents" } },
            { "but", { "* ", "Però " } },
            { "examples", { "Exemples" } },
            { "feature", { "Característica", "Funcionalitat" } },
            { "given", { "* ", "Donat ", "Donada ", "Atès ", "Atesa " } },
            { "rule", { "Rule" } },
            { "scenario", { "Exemple", "Escenari" } },
            { "scenarioOutline", { "Esquema de l'escenari" } },
            { "then", { "* ", "Aleshores ", "Cal " } },
            { "when", { "* ", "Quan " } }
        }
    },
    {
        "cs",
        {
            { "and", { "* ", "A také ", "A " } },
            { "background", { "Pozadí", "Kontext" } },
            { "but", { "* ", "Ale " } },
            { "examples", { "Příklady" } },
            { "feature", { "Požadavek" } },
            { "given", { "* ", "Pokud ", "Za předpokladu " } },
            { "rule", { "Pravidlo" } },
            { "scenario", { "Příklad", "Scénář" } },
            { "scenarioOutline", { "Náčrt Scénáře", "Osnova scénáře" } },
            { "then", { "* ", "Pak " } },
            { "when", { "* ", "Když " } }
        }
    },
    {
        "cy-GB",
        {
            { "and", { "* ", "A " } },
            { "background", { "Cefndir" } },
            { "but", { "* ", "Ond " } },
            { "examples", { "Enghreifftiau" } },
            { "feature", { "Arwedd" } },
            { "given", { "* ", "Anrhegedig a " } },
            { "rule", { "Rule" } },
            { "scenario", { "Enghraifft", "Scenario" } },
            { "scenarioOutline", { "Scenario Amlinellol" } },
            { "then", { "* ", "Yna " } },
            { "when", { "* ", "Pryd " } }
        }
    },
    {
        "da",
        {
            { "and", { "* ", "Og " } },
            { "background", { "Baggrund" } },
            { "but", { "* ", "Men " } },
            { "examples", { "Eksempler" } },
            { "feature", { "Egenskab" } },
            { "given", { "* ", "Givet " } },
            { "rule", { "Regel" } },
            { "scenario", { "Eksempel", "Scenarie" } },
            { "scenarioOutline", { "Abstrakt Scenario" } },
            { "then", { "* ", "Så " } },
            { "when", { "* ", "Når " } }
        }
    },
    {
        "de",
        {
            { "and", { "* ", "Und " } },
            { "background", { "Grundlage", "Hintergrund", "Voraussetzungen", "Vorbedingungen" } },
            { "but", { "* ", "Aber " } },
            { "examples", { "Beispiele" } },
            { "feature", { "Funktionalität", "Funktion" } },
            { "given", { "* ", "Angenommen ", "Gegeben sei ", "Gegeben seien " } },
            { "rule", { "Rule", "Regel" } },
            { "scenario", { "Beispiel", "Szenario" } },
            { "scenarioOutline", { "Szenariogrundriss", "Szenarien" } },
            { "then", { "* ", "Dann " } },
            { "when", { "* ", "Wenn " } }
        }
    },
    {
        "el",
        {
            { "and", { "* ", "Και " } },
            { "background", { "Υπόβαθρο" } },
            { "but", { "* ", "Αλλά " } },
            { "examples", { "Παραδείγματα", "Σενάρια" } },
            { "feature", { "Δυνατότητα", "Λειτουργία" } },
            { "given", { "* ", "Δεδομένου " } },
            { "rule", { "Rule" } },
            { "scenario", { "Παράδειγμα", "Σενάριο" } },
            { "scenarioOutline", { "Περιγραφή Σεναρίου", "Περίγραμμα Σεναρίου" } },
            { "then", { "* ", "Τότε " } },
            { "when", { "* ", "Όταν " } }
        }
    },
    {
        "em",
        {
            { "and", { "* ", "😂" } },
            { "background", { "💤" } },
            { "but", { "* ", "😔" } },
            { "examples", { "📓" } },
            { "feature", { "📚" } },
            { "given", { "* ", "😐" } },
            { "rule", { "Rule" } },
            { "scenario", { "🥒", "📕" } },
            { "scenarioOutline", { "📖" } },
            { "then", { "* ", "🙏" } },
            { "when", { "* ", "🎬" } }
        }
    },
    {
        "en",
        {
            { "and", { "* ", "And " } },
            { "background", { "Background" } },
            { "but", { "* ", "But " } },
            { "examples", { "Examples", "Scenarios" } },
            { "feature", { "Feature", "Business Need", "Ability" } },
            { "given", { "* ", "Given " } },
            { "rule", { "Rule" } },
            { "scenario", { "Example", "Scenario" } },
            { "scenarioOutline", { "Scenario Outline", "Scenario Template" } },
            { "then", { "* ", "Then " } },
            { "when", { "* ", "When " } }
        }
    },
    {
        "en-Scouse",
        {
            { "and", { "* ", "An " } },
            { "background", { "Dis is what went down" } },
            { "but", { "* ", "Buh " } },
            { "examples", { "Examples" } },
            { "feature", { "Feature" } },
            { "given", { "* ", "Givun ", "Youse know when youse got " } },
            { "rule", { "Rule" } },
            { "scenario", { "The thing of it is" } },
            { "scenarioOutline", { "Wharrimean is" } },
            { "then", { "* ", "Dun ", "Den youse gotta " } },
            { "when", { "* ", "Wun ", "Youse know like when " } }
        }
    },
    {
        "en-au",
        {
            { "and", { "* ", "Too right " } },
            { "background", { "First off" } },
            { "but", { "* ", "Yeah nah " } },
            { "examples", { "You'll wanna" } },
            { "feature", { "Pretty much" } },
            { "given", { "* ", "Y'know " } },
            { "rule", { "Rule" } },
            { "scenario", { "Awww, look mate" } },
            { "scenarioOutline", { "Reckon it's like" } },
            { "then", { "* ", "But at the end of the day I reckon " } },
            { "when", { "* ", "It's just unbelievable " } }
        }
    },
    {
        "en-lol",
        {
            { "and", { "* ", "AN " } },
            { "background", { "B4" } },
            { "but", { "* ", "BUT " } },
            { "examples", { "EXAMPLZ" } },
            { "feature", { "OH HAI" } },
            { "given", { "* ", "I CAN HAZ " } },
            { "rule", { "Rule" } },
            { "scenario", { "MISHUN" } },
            { "scenarioOutline", { "MISHUN SRSLY" } },
            { "then", { "* ", "DEN " } },
            { "when", { "* ", "WEN " } }
        }
    },
    {
        "en-old",
        {
            { "and", { "* ", "Ond ", "7 " } },
            { "background", { "Aer", "Ær" } },
            { "but", { "* ", "Ac " } },
            { "examples", { "Se the", "Se þe", "Se ðe" } },
            { "feature", { "Hwaet", "Hwæt" } },
            { "given", { "* ", "Thurh ", "Þurh ", "Ðurh " } },
            { "rule", { "Rule" } },
            { "scenario", { "Swa" } },
            { "scenarioOutline", { "Swa hwaer swa", "Swa hwær swa" } },
            { "then", { "* ", "Tha ", "Þa ", "Ða ", "Tha the ", "Þa þe ", "Ða ðe " } },
            { "when", { "* ", "Bæþsealf ", "Bæþsealfa ", "Bæþsealfe ", "Ciricæw ", "Ciricæwe ", "Ciricæwa " } }
        }
    },
    {
        "en-pirate",
        {
            { "and", { "* ", "Aye " } },
            { "background", { "Yo-ho-ho" } },
            { "but", { "* ", "Avast! " } },
            { "examples", { "Dead men tell no tales" } },
            { "feature", { "Ahoy matey!" } },
            { "given", { "* ", "Gangway! " } },
            { "rule", { "Rule" } },
            { "scenario", { "Heave to" } },
            { "scenarioOutline", { "Shiver me timbers" } },
            { "then", { "* ", "Let go and haul " } },
            { "when", { "* ", "Blimey! " } }
        }
    },
    {
        "en-tx",
        {
            { "and", { "Come hell or high water " } },
            { "background", { "Lemme tell y'all a story" } },
            { "but", { "Well now hold on, I'll you what " } },
            { "examples", { "Now that's a story longer than a cattle drive in July" } },
            { "feature", { "This ain’t my first rodeo", "All gussied up" } },
            { "given", { "Fixin' to ", "All git out " } },
            { "rule", { "Rule " } },
            { "scenario", { "All hat and no cattle" } },
            { "scenarioOutline", { "Serious as a snake bite", "Busy as a hound in flea season" } },
            { "then", { "There’s no tree but bears some fruit " } },
            { "when", { "Quick out of the chute " } }
        }
    },
    {
        "eo",
        {
            { "and", { "* ", "Kaj " } },
            { "background", { "Fono" } },
            { "but", { "* ", "Sed " } },
            { "examples", { "Ekzemploj" } },
            { "feature", { "Trajto" } },
            { "given", { "* ", "Donitaĵo ", "Komence " } },
            { "rule", { "Regulo" } },
            { "scenario", { "Ekzemplo", "Scenaro", "Kazo" } },
            { "scenarioOutline", { "Konturo de la scenaro", "Skizo", "Kazo-skizo" } },
            { "then", { "* ", "Do " } },
            { "when", { "* ", "Se " } }
        }
    },
    {
        "es",
        {
            { "and", { "* ", "Y ", "E " } },
            { "background", { "Antecedentes" } },
            { "but", { "* ", "Pero " } },
            { "examples", { "Ejemplos" } },
            { "feature", { "Característica", "Necesidad del negocio", "Requisito" } },
            { "given", { "* ", "Dado ", "Dada ", "Dados ", "Dadas " } },
            { "rule", { "Regla", "Regla de negocio" } },
            { "scenario", { "Ejemplo", "Escenario" } },
            { "scenarioOutline", { "Esquema del escenario" } },
            { "then", { "* ", "Entonces " } },
            { "when", { "* ", "Cuando " } }
        }
    },
    {
        "et",
        {
            { "and", { "* ", "Ja " } },
            { "background", { "Taust" } },
            { "but", { "* ", "Kuid " } },
            { "examples", { "Juhtumid" } },
            { "feature", { "Omadus" } },
            { "given", { "* ", "Eeldades " } },
            { "rule", { "Reegel" } },
            { "scenario", { "Juhtum", "Stsenaarium" } },
            { "scenarioOutline", { "Raamjuhtum", "Raamstsenaarium" } },
            { "then", { "* ", "Siis " } },
            { "when", { "* ", "Kui " } }
        }
    },
    {
        "fa",
        {
            { "and", { "* ", "و " } },
            { "background", { "زمینه" } },
            { "but", { "* ", "اما " } },
            { "examples", { "نمونه ها" } },
            { "feature", { "وِیژگی" } },
            { "given", { "* ", "با فرض " } },
            { "rule", { "Rule" } },
            { "scenario", { "مثال", "سناریو" } },
            { "scenarioOutline", { "الگوی سناریو" } },
            { "then", { "* ", "آنگاه " } },
            { "when", { "* ", "هنگامی " } }
        }
    },
    {
        "fi",
        {
            { "and", { "* ", "Ja " } },
            { "background", { "Tausta" } },
            { "but", { "* ", "Mutta " } },
            { "examples", { "Tapaukset" } },
            { "feature", { "Ominaisuus" } },
            { "given", { "* ", "Oletetaan " } },
            { "rule", { "Rule" } },
            { "scenario", { "Tapaus" } },
            { "scenarioOutline", { "Tapausaihio" } },
            { "then", { "* ", "Niin " } },
            { "when", { "* ", "Kun " } }
        }
    },
    {
        "fr",
        {
            { "and", { "* ", "Et que ", "Et qu'", "Et " } },
            { "background", { "Contexte" } },
            { "but", { "* ", "Mais que ", "Mais qu'", "Mais " } },
            { "examples", { "Exemples" } },
            { "feature", { "Fonctionnalité" } },
            { "given", { "* ", "Soit ", "Sachant que ", "Sachant qu'", "Sachant ", "Etant donné que ", "Etant donné qu'", "Etant donné ", "Etant donnée ", "Etant donnés ", "Etant données ", "Étant donné que ", "Étant donné qu'", "Étant donné ", "Étant donnée ", "Étant donnés ", "Étant données " } },
            { "rule", { "Règle" } },
            { "scenario", { "Exemple", "Scénario" } },
            { "scenarioOutline", { "Plan du scénario", "Plan du Scénario" } },
            { "then", { "* ", "Alors ", "Donc " } },
            { "when", { "* ", "Quand ", "Lorsque ", "Lorsqu'" } }
        }
    },
    {
        "ga",
        {
            { "and", { "* ", "Agus " } },
            { "background", { "Cúlra" } },
            { "but", { "* ", "Ach " } },
            { "examples", { "Samplaí" } },
            { "feature", { "Gné" } },
            { "given", { "* ", "Cuir i gcás go ", "Cuir i gcás nach ", "Cuir i gcás gur ", "Cuir i gcás nár " } },
            { "rule", { "Riail" } },
            { "scenario", { "Sampla", "Cás" } },
            { "scenarioOutline", { "Cás Achomair" } },
            { "then", { "* ", "Ansin " } },
            { "when", { "* ", "Nuair a ", "Nuair nach ", "Nuair ba ", "Nuair nár " } }
        }
    },
    {
        "gj",
        {
            { "and", { "* ", "અને " } },
            { "background", { "બેકગ્રાઉન્ડ" } },
            { "but", { "* ", "પણ " } },
            { "examples", { "ઉદાહરણો" } },
            { "feature", { "લક્ષણ", "વ્યાપાર જરૂર", "ક્ષમતા" } },
            { "given", { "* ", "આપેલ છે " } },
            { "rule", { "Rule" } },
            { "scenario", { "ઉદાહરણ", "સ્થિતિ" } },
            { "scenarioOutline", { "પરિદ્દશ્ય રૂપરેખા", "પરિદ્દશ્ય ઢાંચો" } },
            { "then", { "* ", "પછી " } },
            { "when", { "* ", "ક્યારે " } }
        }
    },
    {
        "gl",
        {
            { "and", { "* ", "E " } },
            { "background", { "Contexto" } },
            { "but", { "* ", "Mais ", "Pero " } },
            { "examples", { "Exemplos" } },
            { "feature", { "Característica" } },
            { "given", { "* ", "Dado ", "Dada ", "Dados ", "Dadas " } },
            { "rule", { "Rule" } },
            { "scenario", { "Exemplo", "Escenario" } },
            { "scenarioOutline", { "Esbozo do escenario" } },
            { "then", { "* ", "Entón ", "Logo " } },
            { "when", { "* ", "Cando " } }
        }
    },
    {
        "he",
        {
            { "and", { "* ", "וגם " } },
            { "background", { "רקע" } },
            { "but", { "* ", "אבל " } },
            { "examples", { "דוגמאות" } },
            { "feature", { "תכונה" } },
            { "given", { "* ", "בהינתן " } },
            { "rule", { "כלל" } },
            { "scenario", { "דוגמא", "תרחיש" } },
            { "scenarioOutline", { "תבנית תרחיש" } },
            { "then", { "* ", "אז ", "אזי " } },
            { "when", { "* ", "כאשר " } }
        }
    },
    {
        "hi",
        {
            { "and", { "* ", "और ", "तथा " } },
            { "background", { "पृष्ठभूमि" } },
            { "but", { "* ", "पर ", "परन्तु ", "किन्तु " } },
            { "examples", { "उदाहरण" } },
            { "feature", { "रूप लेख" } },
            { "given", { "* ", "अगर ", "यदि ", "चूंकि " } },
            { "rule", { "नियम" } },
            { "scenario", { "परिदृश्य" } },
            { "scenarioOutline", { "परिदृश्य रूपरेखा" } },
            { "then", { "* ", "तब ", "तदा " } },
            { "when", { "* ", "जब ", "कदा " } }
        }
    },
    {
        "hr",
        {
            { "and", { "* ", "I " } },
            { "background", { "Pozadina" } },
            { "but", { "* ", "Ali " } },
            { "examples", { "Primjeri", "Scenariji" } },
            { "feature", { "Osobina", "Mogućnost", "Mogucnost" } },
            { "given", { "* ", "Zadan ", "Zadani ", "Zadano ", "Ukoliko " } },
            { "rule", { "Rule" } },
            { "scenario", { "Primjer", "Scenarij" } },
            { "scenarioOutline", { "Skica", "Koncept" } },
            { "then", { "* ", "Onda " } },
            { "when", { "* ", "Kada ", "Kad " } }
        }
    },
    {
        "ht",
        {
            { "and", { "* ", "Ak ", "Epi ", "E " } },
            { "background", { "Kontèks", "Istorik" } },
            { "but", { "* ", "Men " } },
            { "examples", { "Egzanp" } },
            { "feature", { "Karakteristik", "Mak", "Fonksyonalite" } },
            { "given", { "* ", "Sipoze ", "Sipoze ke ", "Sipoze Ke " } },
            { "rule", { "Rule" } },
            { "scenario", { "Senaryo" } },
            { "scenarioOutline", { "Plan senaryo", "Plan Senaryo", "Senaryo deskripsyon", "Senaryo Deskripsyon", "Dyagram senaryo", "Dyagram Senaryo" } },
            { "then", { "* ", "Lè sa a ", "Le sa a " } },
            { "when", { "* ", "Lè ", "Le " } }
        }
    },
    {
        "hu",
        {
            { "and", { "* ", "És " } },
            { "background", { "Háttér" } },
            { "but", { "* ", "De " } },
            { "examples", { "Példák" } },
            { "feature", { "Jellemző" } },
            { "given", { "* ", "Amennyiben ", "Adott " } },
            { "rule", { "Szabály" } },
            { "scenario", { "Példa", "Forgatókönyv" } },
            { "scenarioOutline", { "Forgatókönyv vázlat" } },
            { "then", { "* ", "Akkor " } },
            { "when", { "* ", "Majd ", "Ha ", "Amikor " } }
        }
    },
    {
        "id",
        {
            { "and", { "* ", "Dan " } },
            { "background", { "Dasar", "Latar Belakang" } },
            { "but", { "* ", "Tapi ", "Tetapi " } },
            { "examples", { "Contoh", "Misal" } },
            { "feature", { "Fitur" } },
            { "given", { "* ", "Dengan ", "Diketahui ", "Diasumsikan ", "Bila ", "Jika " } },
            { "rule", { "Rule", "Aturan" } },
            { "scenario", { "Skenario" } },
            { "scenarioOutline", { "Skenario konsep", "Garis-Besar Skenario" } },
            { "then", { "* ", "Maka ", "Kemudian " } },
            { "when", { "* ", "Ketika " } }
        }
    },
    {
        "is",
        {
            { "and", { "* ", "Og " } },
            { "background", { "Bakgrunnur" } },
            { "but", { "* ", "En " } },
            { "examples", { "Dæmi", "Atburðarásir" } },
            { "feature", { "Eiginleiki" } },
            { "given", { "* ", "Ef " } },
            { "rule", { "Rule" } },
            { "scenario", { "Atburðarás" } },
            { "scenarioOutline", { "Lýsing Atburðarásar", "Lýsing Dæma" } },
            { "then", { "* ", "Þá " } },
            { "when", { "* ", "Þegar " } }
        }
    },
    {
        "it",
        {
            { "and", { "* ", "E ", "Ed " } },
            { "background", { "Contesto" } },
            { "but", { "* ", "Ma " } },
            { "examples", { "Esempi" } },
            { "feature", { "Funzionalità", "Esigenza di Business", "Abilità" } },
            { "given", { "* ", "Dato ", "Data ", "Dati ", "Date " } },
            { "rule", { "Regola" } },
            { "scenario", { "Esempio", "Scenario" } },
            { "scenarioOutline", { "Schema dello scenario" } },
            { "then", { "* ", "Allora " } },
            { "when", { "* ", "Quando " } }
        }
    },
    {
        "ja",
        {
            { "and", { "* ", "且つ", "かつ" } },
            { "background", { "背景" } },
            { "but", { "* ", "然し", "しかし", "但し", "ただし" } },
            { "examples", { "例", "サンプル" } },
            { "feature", { "フィーチャ", "機能" } },
            { "given", { "* ", "前提" } },
            { "rule", { "ルール" } },
            { "scenario", { "シナリオ" } },
            { "scenarioOutline", { "シナリオアウトライン", "シナリオテンプレート", "テンプレ", "シナリオテンプレ" } },
            { "then", { "* ", "ならば" } },
            { "when", { "* ", "もし" } }
        }
    },
    {
        "jv",
        {
            { "and", { "* ", "Lan " } },
            { "background", { "Dasar" } },
            { "but", { "* ", "Tapi ", "Nanging ", "Ananging " } },
            { "examples", { "Conto", "Contone" } },
            { "feature", { "Fitur" } },
            { "given", { "* ", "Nalika ", "Nalikaning " } },
            { "rule", { "Rule" } },
            { "scenario", { "Skenario" } },
            { "scenarioOutline", { "Konsep skenario" } },
            { "then", { "* ", "Njuk ", "Banjur " } },
            { "when", { "* ", "Manawa ", "Menawa " } }
        }
    },
    {
        "ka",
        {
            { "and", { "* ", "და ", "ასევე " } },
            { "background", { "კონტექსტი" } },
            { "but", { "* ", "მაგრამ ", "თუმცა " } },
            { "examples", { "მაგალითები" } },
            { "feature", { "თვისება", "მოთხოვნა" } },
            { "given", { "* ", "მოცემული ", "მოცემულია ", "ვთქვათ " } },
            { "rule", { "წესი" } },
            { "scenario", { "მაგალითად", "მაგალითი", "მაგ", "სცენარი" } },
            { "scenarioOutline", { "სცენარის ნიმუში", "სცენარის შაბლონი", "ნიმუში", "შაბლონი" } },
            { "then", { "* ", "მაშინ " } },
            { "when", { "* ", "როდესაც ", "როცა ", "როგორც კი ", "თუ " } }
        }
    },
    {
        "kn",
        {
            { "and", { "* ", "ಮತ್ತು " } },
            { "background", { "ಹಿನ್ನೆಲೆ" } },
            { "but", { "* ", "ಆದರೆ " } },
            { "examples", { "ಉದಾಹರಣೆಗಳು" } },
            { "feature", { "ಹೆಚ್ಚಳ" } },
            { "given", { "* ", "ನೀಡಿದ " } },
            { "rule", { "Rule" } },
            { "scenario", { "ಉದಾಹರಣೆ", "ಕಥಾಸಾರಾಂಶ" } },
            { "scenarioOutline", { "ವಿವರಣೆ" } },
            { "then", { "* ", "ನಂತರ " } },
            { "when", { "* ", "ಸ್ಥಿತಿಯನ್ನು " } }
        }
    },
    {
        "ko",
        {
            { "and", { "* ", "그리고 " } },
            { "background", { "배경" } },
            { "but", { "* ", "하지만 ", "단 " } },
            { "examples", { "예" } },
            { "feature", { "기능" } },
            { "given", { "* ", "조건 ", "먼저 " } },
            { "rule", { "Rule" } },
            { "scenario", { "시나리오" } },
            { "scenarioOutline", { "시나리오 개요" } },
            { "then", { "* ", "그러면 " } },
            { "when", { "* ", "만일 ", "만약 " } }
        }
    },
    {
        "lt",
        {
            { "and", { "* ", "Ir " } },
            { "background", { "Kontekstas" } },
            { "but", { "* ", "Bet " } },
            { "examples", { "Pavyzdžiai", "Scenarijai", "Variantai" } },
            { "feature", { "Savybė" } },
            { "given", { "* ", "Duota " } },
            { "rule", { "Rule" } },
            { "scenario", { "Pavyzdys", "Scenarijus" } },
            { "scenarioOutline", { "Scenarijaus šablonas" } },
            { "then", { "* ", "Tada " } },
            { "when", { "* ", "Kai " } }
        }
    },
    {
        "lu",
        {
            { "and", { "* ", "an ", "a " } },
            { "background", { "Hannergrond" } },
            { "but", { "* ", "awer ", "mä " } },
            { "examples", { "Beispiller" } },
            { "feature", { "Funktionalitéit" } },
            { "given", { "* ", "ugeholl " } },
            { "rule", { "Rule" } },
            { "scenario", { "Beispill", "Szenario" } },
            { "scenarioOutline", { "Plang vum Szenario" } },
            { "then", { "* ", "dann " } },
            { "when", { "* ", "wann " } }
        }
    },
    {
        "lv",
        {
            { "and", { "* ", "Un " } },
            { "background", { "Konteksts", "Situācija" } },
            { "but", { "* ", "Bet " } },
            { "examples", { "Piemēri", "Paraugs" } },
            { "feature", { "Funkcionalitāte", "Fīča" } },
            { "given", { "* ", "Kad " } },
            { "rule", { "Rule" } },
            { "scenario", { "Piemērs", "Scenārijs" } },
            { "scenarioOutline", { "Scenārijs pēc parauga" } },
            { "then", { "* ", "Tad " } },
            { "when", { "* ", "Ja " } }
        }
    },
    {
        "mk-Cyrl",
        {
            { "and", { "* ", "И " } },
            { "background", { "Контекст", "Содржина" } },
            { "but", { "* ", "Но " } },
            { "examples", { "Примери", "Сценарија" } },
            { "feature", { "Функционалност", "Бизнис потреба", "Можност" } },
            { "given", { "* ", "Дадено ", "Дадена " } },
            { "rule", { "Rule" } },
            { "scenario", { "Пример", "Сценарио", "На пример" } },
            { "scenarioOutline", { "Преглед на сценарија", "Скица", "Концепт" } },
            { "then", { "* ", "Тогаш " } },
            { "when", { "* ", "Кога " } }
        }
    },
    {
        "mk-Latn",
        {
            { "and", { "* ", "I " } },
            { "background", { "Kontekst", "Sodrzhina" } },
            { "but", { "* ", "No " } },
            { "examples", { "Primeri", "Scenaria" } },
            { "feature", { "Funkcionalnost", "Biznis potreba", "Mozhnost" } },
            { "given", { "* ", "Dadeno ", "Dadena " } },
            { "rule", { "Rule" } },
            { "scenario", { "Scenario", "Na primer" } },
            { "scenarioOutline", { "Pregled na scenarija", "Skica", "Koncept" } },
            { "then", { "* ", "Togash " } },
            { "when", { "* ", "Koga " } }
        }
    },
    {
        "mn",
        {
            { "and", { "* ", "Мөн ", "Тэгээд " } },
            { "background", { "Агуулга" } },
            { "but", { "* ", "Гэхдээ ", "Харин " } },
            { "examples", { "Тухайлбал" } },
            { "feature", { "Функц", "Функционал" } },
            { "given", { "* ", "Өгөгдсөн нь ", "Анх " } },
            { "rule", { "Rule" } },
            { "scenario", { "Сценар" } },
            { "scenarioOutline", { "Сценарын төлөвлөгөө" } },
            { "then", { "* ", "Тэгэхэд ", "Үүний дараа " } },
            { "when", { "* ", "Хэрэв " } }
        }
    },
    {
        "ne",
        {
            { "and", { "* ", "र ", "अनि " } },
            { "background", { "पृष्ठभूमी" } },
            { "but", { "* ", "तर " } },
            { "examples", { "उदाहरण", "उदाहरणहरु" } },
            { "feature", { "सुविधा", "विशेषता" } },
            { "given", { "* ", "दिइएको ", "दिएको ", "यदि " } },
            { "rule", { "नियम" } },
            { "scenario", { "परिदृश्य" } },
            { "scenarioOutline", { "परिदृश्य रूपरेखा" } },
            { "then", { "* ", "त्यसपछि ", "अनी " } },
            { "when", { "* ", "जब " } }
        }
    },
    {
        "nl",
        {
            { "and", { "* ", "En " } },
            { "background", { "Achtergrond" } },
            { "but", { "* ", "Maar " } },
            { "examples", { "Voorbeelden" } },
            { "feature", { "Functionaliteit" } },
            { "given", { "* ", "Gegeven ", "Stel " } },
            { "rule", { "Regel" } },
            { "scenario", { "Voorbeeld", "Scenario" } },
            { "scenarioOutline", { "Abstract Scenario" } },
            { "then", { "* ", "Dan " } },
            { "when", { "* ", "Als ", "Wanneer " } }
        }
    },
    {
        "no",
        {
            { "and", { "* ", "Og " } },
            { "background", { "Bakgrunn" } },
            { "but", { "* ", "Men " } },
            { "examples", { "Eksempler" } },
            { "feature", { "Egenskap" } },
            { "given", { "* ", "Gitt " } },
            { "rule", { "Regel" } },
            { "scenario", { "Eksempel", "Scenario" } },
            { "scenarioOutline", { "Scenariomal", "Abstrakt Scenario" } },
            { "then", { "* ", "Så " } },
            { "when", { "* ", "Når " } }
        }
    },
    {
        "pa",
        {
            { "and", { "* ", "ਅਤੇ " } },
            { "background", { "ਪਿਛੋਕੜ" } },
            { "but", { "* ", "ਪਰ " } },
            { "examples", { "ਉਦਾਹਰਨਾਂ" } },
            { "feature", { "ਖਾਸੀਅਤ", "ਮੁਹਾਂਦਰਾ", "ਨਕਸ਼ ਨੁਹਾਰ" } },
            { "given", { "* ", "ਜੇਕਰ ", "ਜਿਵੇਂ ਕਿ " } },
            { "rule", { "Rule" } },
            { "scenario", { "ਉਦਾਹਰਨ", "ਪਟਕਥਾ" } },
            { "scenarioOutline", { "ਪਟਕਥਾ ਢਾਂਚਾ", "ਪਟਕਥਾ ਰੂਪ ਰੇਖਾ" } },
            { "then", { "* ", "ਤਦ " } },
            { "when", { "* ", "ਜਦੋਂ " } }
        }
    },
    {
        "pl",
        {
            { "and", { "* ", "Oraz ", "I " } },
            { "background", { "Założenia" } },
            { "but", { "* ", "Ale " } },
            { "examples", { "Przykłady" } },
            { "feature", { "Właściwość", "Funkcja", "Aspekt", "Potrzeba biznesowa" } },
            { "given", { "* ", "Zakładając ", "Mając ", "Zakładając, że " } },
            { "rule", { "Zasada", "Reguła" } },
            { "scenario", { "Przykład", "Scenariusz" } },
            { "scenarioOutline", { "Szablon scenariusza" } },
            { "then", { "* ", "Wtedy " } },
            { "when", { "* ", "Jeżeli ", "Jeśli ", "Gdy ", "Kiedy " } }
        }
    },
    {
        "pt",
        {
            { "and", { "* ", "E " } },
            { "background", { "Contexto", "Cenário de Fundo", "Cenario de Fundo", "Fundo" } },
            { "but", { "* ", "Mas " } },
            { "examples", { "Exemplos", "Cenários", "Cenarios" } },
            { "feature", { "Funcionalidade", "Característica", "Caracteristica" } },
            { "given", { "* ", "Dado ", "Dada ", "Dados ", "Dadas " } },
            { "rule", { "Regra" } },
            { "scenario", { "Exemplo", "Cenário", "Cenario" } },
            { "scenarioOutline", { "Esquema do Cenário", "Esquema do Cenario", "Delineação do Cenário", "Delineacao do Cenario" } },
            { "then", { "* ", "Então ", "Entao " } },
            { "when", { "* ", "Quando " } }
        }
    },
    {
        "ro",
        {
            { "and", { "* ", "Si ", "Și ", "Şi " } },
            { "background", { "Context" } },
            { "but", { "* ", "Dar " } },
            { "examples", { "Exemple" } },
            { "feature", { "Functionalitate", "Funcționalitate", "Funcţionalitate" } },
            { "given", { "* ", "Date fiind ", "Dat fiind ", "Dată fiind", "Dati fiind ", "Dați fiind ", "Daţi fiind " } },
            { "rule", { "Rule" } },
            { "scenario", { "Exemplu", "Scenariu" } },
            { "scenarioOutline", { "Structura scenariu", "Structură scenariu" } },
            { "then", { "* ", "Atunci " } },
            { "when", { "* ", "Cand ", "Când " } }
        }
    },
    {
        "ru",
        {
            { "and", { "* ", "И ", "К тому же ", "Также " } },
            { "background", { "Предыстория", "Контекст" } },
            { "but", { "* ", "Но ", "А ", "Иначе " } },
            { "examples", { "Примеры" } },
            { "feature", { "Функция", "Функциональность", "Функционал", "Свойство", "Фича" } },
            { "given", { "* ", "Допустим ", "Дано ", "Пусть " } },
            { "rule", { "Правило" } },
            { "scenario", { "Пример", "Сценарий" } },
            { "scenarioOutline", { "Структура сценария", "Шаблон сценария" } },
            { "then", { "* ", "То ", "Затем ", "Тогда " } },
            { "when", { "* ", "Когда ", "Если " } }
        }
    },
    {
        "sk",
        {
            { "and", { "* ", "A ", "A tiež ", "A taktiež ", "A zároveň " } },
            { "background", { "Pozadie" } },
            { "but", { "* ", "Ale " } },
            { "examples", { "Príklady" } },
            { "feature", { "Požiadavka", "Funkcia", "Vlastnosť" } },
            { "given", { "* ", "Pokiaľ ", "Za predpokladu " } },
            { "rule", { "Rule" } },
            { "scenario", { "Príklad", "Scenár" } },
            { "scenarioOutline", { "Náčrt Scenáru", "Náčrt Scenára", "Osnova Scenára" } },
            { "then", { "* ", "Tak ", "Potom " } },
            { "when", { "* ", "Keď ", "Ak " } }
        }
    },
    {
        "sl",
        {
            { "and", { "In ", "Ter " } },
            { "background", { "Kontekst", "Osnova", "Ozadje" } },
            { "but", { "Toda ", "Ampak ", "Vendar " } },
            { "examples", { "Primeri", "Scenariji" } },
            { "feature", { "Funkcionalnost", "Funkcija", "Možnosti", "Moznosti", "Lastnost", "Značilnost" } },
            { "given", { "Dano ", "Podano ", "Zaradi ", "Privzeto " } },
            { "rule", { "Rule" } },
            { "scenario", { "Primer", "Scenarij" } },
            { "scenarioOutline", { "Struktura scenarija", "Skica", "Koncept", "Oris scenarija", "Osnutek" } },
            { "then", { "Nato ", "Potem ", "Takrat " } },
            { "when", { "Ko ", "Ce ", "Če ", "Kadar " } }
        }
    },
    {
        "sr-Cyrl",
        {
            { "and", { "* ", "И " } },
            { "background", { "Контекст", "Основа", "Позадина" } },
            { "but", { "* ", "Али " } },
            { "examples", { "Примери", "Сценарији" } },
            { "feature", { "Функционалност", "Могућност", "Особина" } },
            { "given", { "* ", "За дато ", "За дате ", "За дати " } },
            { "rule", { "Правило" } },
            { "scenario", { "Пример", "Сценарио", "Пример" } },
            { "scenarioOutline", { "Структура сценарија", "Скица", "Концепт" } },
            { "then", { "* ", "Онда " } },
            { "when", { "* ", "Када ", "Кад " } }
        }
    },
    {
        "sr-Latn",
        {
            { "and", { "* ", "I " } },
            { "background", { "Kontekst", "Osnova", "Pozadina" } },
            { "but", { "* ", "Ali " } },
            { "examples", { "Primeri", "Scenariji" } },
            { "feature", { "Funkcionalnost", "Mogućnost", "Mogucnost", "Osobina" } },
            { "given", { "* ", "Za dato ", "Za date ", "Za dati " } },
            { "rule", { "Pravilo" } },
            { "scenario", { "Scenario", "Primer" } },
            { "scenarioOutline", { "Struktura scenarija", "Skica", "Koncept" } },
            { "then", { "* ", "Onda " } },
            { "when", { "* ", "Kada ", "Kad " } }
        }
    },
    {
        "sv",
        {
            { "and", { "* ", "Och " } },
            { "background", { "Bakgrund" } },
            { "but", { "* ", "Men " } },
            { "examples", { "Exempel" } },
            { "feature", { "Egenskap" } },
            { "given", { "* ", "Givet " } },
            { "rule", { "Regel" } },
            { "scenario", { "Scenario" } },
            { "scenarioOutline", { "Abstrakt Scenario", "Scenariomall" } },
            { "then", { "* ", "Så " } },
            { "when", { "* ", "När " } }
        }
    },
    {
        "ta",
        {
            { "and", { "* ", "மேலும் ", "மற்றும் " } },
            { "background", { "பின்னணி" } },
            { "but", { "* ", "ஆனால் " } },
            { "examples", { "எடுத்துக்காட்டுகள்", "காட்சிகள்", "நிலைமைகளில்" } },
            { "feature", { "அம்சம்", "வணிக தேவை", "திறன்" } },
            { "given", { "* ", "கொடுக்கப்பட்ட " } },
            { "rule", { "Rule" } },
            { "scenario", { "உதாரணமாக", "காட்சி" } },
            { "scenarioOutline", { "காட்சி சுருக்கம்", "காட்சி வார்ப்புரு" } },
            { "then", { "* ", "அப்பொழுது " } },
            { "when", { "* ", "எப்போது " } }
        }
    },
    {
        "th",
        {
            { "and", { "* ", "และ " } },
            { "background", { "แนวคิด" } },
            { "but", { "* ", "แต่ " } },
            { "examples", { "ชุดของตัวอย่าง", "ชุดของเหตุการณ์" } },
            { "feature", { "โครงหลัก", "ความต้องการทางธุรกิจ", "ความสามารถ" } },
            { "given", { "* ", "กำหนดให้ " } },
            { "rule", { "Rule" } },
            { "scenario", { "เหตุการณ์" } },
            { "scenarioOutline", { "สรุปเหตุการณ์", "โครงสร้างของเหตุการณ์" } },
            { "then", { "* ", "ดังนั้น " } },
            { "when", { "* ", "เมื่อ " } }
        }
    },
    {
        "te",
        {
            { "and", { "* ", "మరియు " } },
            { "background", { "నేపథ్యం" } },
            { "but", { "* ", "కాని " } },
            { "examples", { "ఉదాహరణలు" } },
            { "feature", { "గుణము" } },
            { "given", { "* ", "చెప్పబడినది " } },
            { "rule", { "Rule" } },
            { "scenario", { "ఉదాహరణ", "సన్నివేశం" } },
            { "scenarioOutline", { "కథనం" } },
            { "then", { "* ", "అప్పుడు " } },
            { "when", { "* ", "ఈ పరిస్థితిలో " } }
        }
    },
    {
        "tlh",
        {
            { "and", { "* ", "'ej ", "latlh " } },
            { "background", { "mo'" } },
            { "but", { "* ", "'ach ", "'a " } },
            { "examples", { "ghantoH", "lutmey" } },
            { "feature", { "Qap", "Qu'meH 'ut", "perbogh", "poQbogh malja'", "laH" } },
            { "given", { "* ", "ghu' noblu' ", "DaH ghu' bejlu' " } },
            { "rule", { "Rule" } },
            { "scenario", { "lut" } },
            { "scenarioOutline", { "lut chovnatlh" } },
            { "then", { "* ", "vaj " } },
            { "when", { "* ", "qaSDI' " } }
        }
    },
    {
        "tr",
        {
            { "and", { "* ", "Ve " } },
            { "background", { "Geçmiş" } },
            { "but", { "* ", "Fakat ", "Ama " } },
            { "examples", { "Örnekler" } },
            { "feature", { "Özellik" } },
            { "given", { "* ", "Diyelim ki " } },
            { "rule", { "Kural" } },
            { "scenario", { "Örnek", "Senaryo" } },
            { "scenarioOutline", { "Senaryo taslağı" } },
            { "then", { "* ", "O zaman " } },
            { "when", { "* ", "Eğer ki " } }
        }
    },
    {
        "tt",
        {
            { "and", { "* ", "Һәм ", "Вә " } },
            { "background", { "Кереш" } },
            { "but", { "* ", "Ләкин ", "Әмма " } },
            { "examples", { "Үрнәкләр", "Мисаллар" } },
            { "feature", { "Мөмкинлек", "Үзенчәлеклелек" } },
            { "given", { "* ", "Әйтик " } },
            { "rule", { "Rule" } },
            { "scenario", { "Сценарий" } },
            { "scenarioOutline", { "Сценарийның төзелеше" } },
            { "then", { "* ", "Нәтиҗәдә " } },
            { "when", { "* ", "Әгәр " } }
        }
    },
    {
        "uk",
        {
            { "and", { "* ", "І ", "А також ", "Та " } },
            { "background", { "Передумова" } },
            { "but", { "* ", "Але " } },
            { "examples", { "Приклади" } },
            { "feature", { "Функціонал" } },
            { "given", { "* ", "Припустимо ", "Припустимо, що ", "Нехай ", "Дано " } },
            { "rule", { "Rule" } },
            { "scenario", { "Приклад", "Сценарій" } },
            { "scenarioOutline", { "Структура сценарію" } },
            { "then", { "* ", "То ", "Тоді " } },
            { "when", { "* ", "Якщо ", "Коли " } }
        }
    },
    {
        "ur",
        {
            { "and", { "* ", "اور " } },
            { "background", { "پس منظر" } },
            { "but", { "* ", "لیکن " } },
            { "examples", { "مثالیں" } },
            { "feature", { "صلاحیت", "کاروبار کی ضرورت", "خصوصیت" } },
            { "given", { "* ", "اگر ", "بالفرض ", "فرض کیا " } },
            { "rule", { "Rule" } },
            { "scenario", { "منظرنامہ" } },
            { "scenarioOutline", { "منظر نامے کا خاکہ" } },
            { "then", { "* ", "پھر ", "تب " } },
            { "when", { "* ", "جب " } }
        }
    },
    {
        "uz",
        {
            { "and", { "* ", "Ва " } },
            { "background", { "Тарих" } },
            { "but", { "* ", "Лекин ", "Бирок ", "Аммо " } },
            { "examples", { "Мисоллар" } },
            { "feature", { "Функционал" } },
            { "given", { "* ", "Belgilangan " } },
            { "rule", { "Rule" } },
            { "scenario", { "Сценарий" } },
            { "scenarioOutline", { "Сценарий структураси" } },
            { "then", { "* ", "Унда " } },
            { "when", { "* ", "Агар " } }
        }
    },
    {
        "vi",
        {
            { "and", { "* ", "Và " } },
            { "background", { "Bối cảnh" } },
            { "but", { "* ", "Nhưng " } },
            { "examples", { "Dữ liệu" } },
            { "feature", { "Tính năng" } },
            { "given", { "* ", "Biết ", "Cho " } },
            { "rule", { "Quy tắc" } },
            { "scenario", { "Tình huống", "Kịch bản" } },
            { "scenarioOutline", { "Khung tình huống", "Khung kịch bản" } },
            { "then", { "* ", "Thì " } },
            { "when", { "* ", "Khi " } }
        }
    },
    {
        "zh-CN",
        {
            { "and", { "* ", "而且", "并且", "同时" } },
            { "background", { "背景" } },
            { "but", { "* ", "但是" } },
            { "examples", { "例子" } },
            { "feature", { "功能" } },
            { "given", { "* ", "假如", "假设", "假定" } },
            { "rule", { "Rule", "规则" } },
            { "scenario", { "场景", "剧本" } },
            { "scenarioOutline", { "场景大纲", "剧本大纲" } },
            { "then", { "* ", "那么" } },
            { "when", { "* ", "当" } }
        }
    },
    {
        "ml",
        {
            { "and", { "* ", "ഒപ്പം" } },
            { "background", { "പശ്ചാത്തലം" } },
            { "but", { "* ", "പക്ഷേ" } },
            { "examples", { "ഉദാഹരണങ്ങൾ" } },
            { "feature", { "സവിശേഷത" } },
            { "given", { "* ", "നൽകിയത്" } },
            { "rule", { "നിയമം" } },
            { "scenario", { "രംഗം" } },
            { "scenarioOutline", { "സാഹചര്യത്തിന്റെ രൂപരേഖ" } },
            { "then", { "* ", "പിന്നെ" } },
            { "when", { "എപ്പോൾ" } }
        }
    },
    {
        "zh-TW",
        {
            { "and", { "* ", "而且", "並且", "同時" } },
            { "background", { "背景" } },
            { "but", { "* ", "但是" } },
            { "examples", { "例子" } },
            { "feature", { "功能" } },
            { "given", { "* ", "假如", "假設", "假定" } },
            { "rule", { "Rule" } },
            { "scenario", { "場景", "劇本" } },
            { "scenarioOutline", { "場景大綱", "劇本大綱" } },
            { "then", { "* ", "那麼" } },
            { "when", { "* ", "當" } }
        }
    },
    {
        "mr",
        {
            { "and", { "* ", "आणि ", "तसेच " } },
            { "background", { "पार्श्वभूमी" } },
            { "but", { "* ", "पण ", "परंतु " } },
            { "examples", { "उदाहरण" } },
            { "feature", { "वैशिष्ट्य", "सुविधा" } },
            { "given", { "* ", "जर", "दिलेल्या प्रमाणे " } },
            { "rule", { "नियम" } },
            { "scenario", { "परिदृश्य" } },
            { "scenarioOutline", { "परिदृश्य रूपरेखा" } },
            { "then", { "* ", "मग ", "तेव्हा " } },
            { "when", { "* ", "जेव्हा " } }
        }
    },
    {
        "amh",
        {
            { "and", { "* ", "እና " } },
            { "background", { "ቅድመ ሁኔታ", "መነሻ", "መነሻ ሀሳብ" } },
            { "but", { "* ", "ግን " } },
            { "examples", { "ምሳሌዎች", "ሁናቴዎች" } },
            { "feature", { "ስራ", "የተፈለገው ስራ", "የሚፈለገው ድርጊት" } },
            { "given", { "* ", "የተሰጠ " } },
            { "rule", { "ህግ" } },
            { "scenario", { "ምሳሌ", "ሁናቴ" } },
            { "scenarioOutline", { "ሁናቴ ዝርዝር", "ሁናቴ አብነት" } },
            { "then", { "* ", "ከዚያ " } },
            { "when", { "* ", "መቼ " } }
        }
    }
    };

    return kwms;}

const keywords_map&
keywords(const std::string_view& language)
{
    return all_keywords().at(language);
}

}

