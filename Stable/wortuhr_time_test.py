import requests
import time

# IP der WortUhr, die du testen möchtst
base_url = "http://192.168.2.157"  # Ersetze dies durch deine tatsächliche IP

for x in range(24):  # x von 0 bis 24
    #for y in range(60):  # y von 0 bis 60 # Test in Minuten Takt
    for y in [0, 15, 30, 45]:   # Test in viertel Stunden Takt
        # Erstelle die vollständige URL mit den Variablen
        url = f"{base_url}/?year=1900&month=01&day=00&hour=x={x}&min=y={y}&action=savedatetime"
        try:
            response = requests.get(url)
            # Optional: Ausgabe des Statuscodes oder der Antwort
            print(f"Aufruf: {url} - Status: {response.status_code}")
            time.sleep(1)
        except requests.exceptions.RequestException as e:
            print(f"Fehler beim Aufruf von {url}: {e}")