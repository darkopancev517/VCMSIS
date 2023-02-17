<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Regellisten | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="firewall-full-rulesets.php" title="35. Kapitel - Vollst&auml;ndige Regellisten"><link rel="prev" href="firewall-full-rulesets.php" title="35. Kapitel - Vollst&auml;ndige Regellisten"><link rel="next" href="firewall-additional-functions.php" title="36. Kapitel - Weitere Funktionen">
    <meta http-equiv="content-language" content="de">
  </head><body>
          
    <!-- header start -->

<div id="header">

<div id="logo">
	<a href="../../../index.html">
		<div id="logo_screen"><img src="../../../pictures/intra2net.gif" alt="Intra2net AG"></div>
		<div id="logo_print"><img src="../../../pictures/intra2net_print.gif" alt="Intra2net AG"></div>
	</a>
</div>

<div id="search">
	<form name="formsearch" method="get" action="http://www.intra2net.com/search/search.cgi">
		<input type="text" name="q" maxlength="64" id="searchinput" value="">
		<input type="image" name="submit" src="../../../pictures/search.gif" alt="Suche">
	</form>
</div>


<nav id="navigation">

<a href="firewall-full-rulesets-rulesets.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="firewall-full-rulesets-rulesets.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

<ul class="navbar">

<li id="Produkte"><a href="../../../../en/products/index.html">Produkte</a>
	<div class="dropdown">
		<div class="navgrid">
			<div class="navgrid-unit navcol1_of_3">
				<h4>SOFTWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/index.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/intranator.php">Business Server</a></li>
						<li><a href="../../../produkte/security_gateway.php">Security Gateway</a></li>
						<li><a href="../../../produkte/network_security.php">Network Security</a></li>
						<li><a href="../../../produkte/lizenzen/index.php">Lizenzbestimmungen</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>HARDWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/hardware.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/appliance_eco.php">Appliance Eco</a></li>
						<li><a href="../../../produkte/appliance_pro.php">Appliance Pro</a></li>
						<li><a href="../../../produkte/appliance_ultimate.php">Appliance Ultimate</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>REFERENZEN</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/anwenderberichte.php">Anwenderberichte</a></li>
						<li><a href="../../../produkte/kundenstimmen.php">Kundenstimmen</a></li>
						<li><a href="../../../produkte/pressestimmen.php">Pressestimmen</a></li>
					</ul>
			</div>
		</div> <!-- close .grid div -->
	</div> <!-- close .dropdown div -->
</li>

<li id="Download"><a href="../../../download.1">Download</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../download/index.php">Software</a></li>
			<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
			<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
		</ul>
	</div>
</li>

<li id="Support" class="selected"><a href="../../../../en/support/index.html">Support</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../anfrage.php">Support-Anfrage</a></li>
			<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
			<li><a href="http://forum.intra2net.com/">Forum</a></li>
			<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
			<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
			<li><a href="../../schulung.php">Schulung</a></li>
			<li><a href="../../fernwartung.php">Fernwartung</a></li>
		</ul>
	</div>
</li>

<li id="Kaufen"><a href="../../../kaufen/index.html">Kaufen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../kaufen/index.php">Partner finden</a></li>
			<li><a href="../../../partner-werden">Partner werden</a></li>
			<li><a href="http://partner.intra2net.com/">Partnerweb</a></li>
		</ul>
	</div>
</li>

<li id="Unternehmen"><a href="../../../unternehmen/index.html">Unternehmen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
			<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
			<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
			<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
		</ul>
	</div>
</li>

</ul> <!-- close #navbar ul -->

</nav>

</div> <!-- close #header div -->


<div id="page">


<div id="content">

<!-- header end -->

    <div id="manual">
    <!-- content start -->

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">35.2. Regellisten</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="firewall-full-rulesets.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">35. Kapitel - Vollst&auml;ndige Regellisten</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="firewall-additional-functions.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="firewall-full-rulesets-rulesets"></a>35.2. Regellisten</h2></div></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="firewall-full-rulesets-rulesets-basics"></a>35.2.1. Grundeinstellungen</h3></div></div></div><p>Bei jeder Regelliste wird eingestellt, ob Sie f&uuml;r das Lokale Netz und VPNs oder f&uuml;r den
        Zugriff vom Internet (Provider) genutzt werden kann. Diese Unterscheidung ist ein
        zus&auml;tzlicher Schutz, damit man nicht aus Versehen z.B. eine Regel mit Vollzugriff f&uuml;r
        Verbindungen aus dem Internet festlegen kann.</p><a class="indexterm" name="firewall-full-rulesets-rulesets-basics1"></a><p>Beinahe alle Protokolle erwarten auf ein gesendetes IP-Paket eine Antwort. Bei TCP
        k&ouml;nnen z.B. &uuml;berhaupt erst Daten flie&szlig;en, sobald die Gegenstelle den Aufbau der Verbindung
        best&auml;tigt hat. Daher muss eigentlich f&uuml;r fast alle Protokolle nicht nur der Hinweg der Pakete
        in der Firewall zugelassen werden, sondern auch der R&uuml;ckweg f&uuml;r die Antwortpakete ge&ouml;ffnet
        werden.</p><p>Damit man nun nicht jede Regel an zwei oder mehr Stellen eintragen muss, kann der
        Intranator jedes Antwortpaket automatisch der entsprechenden Verbindung zuordnen (Stateful
        Firewall). &Uuml;ber die Option <span class="guimenuitem">Automatische Antwortregel</span> werden diese
        Antwortpakete automatisch durch die Firewall gelassen. Nur in ganz wenigen Ausnahmen macht
        es Sinn, auf die automatische Antwortregel zu verzichten.</p><a class="indexterm" name="d0e11258"></a></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="firewall-full-rulesets-rulesets-traversal"></a>35.2.2. Durchlaufen der Regelliste</h3></div></div></div><a class="indexterm" name="firewall-full-rulesets-rulesets-traversal1"></a><p>Eine Regelliste wird von oben nach unten abgearbeitet. Treffen alle Bedingungen einer
        Regel zu (&#8222;Match&#8220;), wird die Aktion der Regel ausgef&uuml;hrt. Bei den meisten Aktionen ist der
        Durchlauf f&uuml;r dieses Paket beendet, sp&auml;tere Regeln haben keine Auswirkung (die erste
        zutreffende Regel entscheidet). </p><p>Triff keine Regel einer Regelliste zu, wird das Paket verworfen (implizites Deny). Dies
        wird durch die unver&auml;nderliche Regel am Schluss der Regelliste visualisiert. Wird ein Paket
        an eine andere Regelliste weitergeleitet und trifft dort keine Regel zu, wird das Paket an
        die urspr&uuml;ngliche Regelliste zur&uuml;ckverwiesen. Die in der weitergeleiteten Regelliste
        angezeigte &#8222;Deny&#8220; Regel gilt nicht f&uuml;r den R&uuml;cksprung.</p><a class="indexterm" name="d0e11271"></a></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="firewall-full-rulesets-rulesets-combination"></a>35.2.3. Verkn&uuml;pfung der Regel-Kriterien</h3></div></div></div><p>Sind verschiedene Kriterien einer Regel aktiviert (z.B. Quelle, Dienst und
        Verbindungsstatus), so m&uuml;ssen alle diese Kriterien zum Ausf&uuml;hren der Aktion auf das Paket
        zutreffen. Sind bei einer Regel keine Kriterien eingetragen, wird die Aktion immer
        ausgef&uuml;hrt.</p><p>Bei den Kriterien &#8222;Quelle&#8220;, &#8222;Ziel&#8220; und &#8222;Dienst&#8220; k&ouml;nnen mehrere M&ouml;glichkeiten eingestellt
        werden. Es reicht, wenn eine davon zutrifft (Oder-Verkn&uuml;pfung).</p><p>Beispiel:</p><div class="informaltable"><table border="0"><colgroup><col><col></colgroup><tbody><tr><td align="left">
                <div class="mediaobject"><img src="../images/firewall/quelle.png"></div>
              </td><td align="left">
                <div class="mediaobject"><img src="../images/firewall/dienste.png"></div>
              </td></tr></tbody></table></div><div class="informaltable"><table border="1"><colgroup><col><col><col></colgroup><thead><tr><th>Quelle</th><th>Dienst</th><th>Trifft zu</th></tr></thead><tbody><tr><td>Rechner1</td><td>Ping</td><td>Nein</td></tr><tr><td>Rechner1</td><td>HTTP</td><td>Ja</td></tr><tr><td>Rechner1</td><td>FTP</td><td>Ja</td></tr><tr><td>Rechner2</td><td>HTTP</td><td>Ja</td></tr><tr><td>Rechner2</td><td>FTP</td><td>Ja</td></tr></tbody></table></div><p>Es k&ouml;nnen auch Objekte mit &#8222;Not&#8220; in eine Regel eingef&uuml;gt werden. Die Aktion wird
        ausgef&uuml;hrt, wenn dieses Objekt nicht im Paket vorkommt. Werden mehrere Objekte mit &#8222;Not&#8220;
        eingestellt, darf keines davon vorkommen (Und-Verkn&uuml;pfung).</p><p>Werden Objekte mit &#8222;Not&#8220; und normale Objekte in einer Bedingung gemeinsam verwendet,
        muss mindestens eines der normalen Objekte zutreffen (Oder-Verkn&uuml;pfung), aber keines der
        Objekte mit &#8222;Not&#8220; (Und-Verkn&uuml;pfung).</p><p>Beispiel:</p><p>
        </p><div class="mediaobject"><img src="../images/firewall/quelle_not.png"></div><p>
      </p><div class="informaltable"><table border="1"><colgroup><col><col></colgroup><thead><tr><th>Quelle</th><th>Trifft zu</th></tr></thead><tbody><tr><td>Rechner1</td><td>Nein</td></tr><tr><td>Rechner2</td><td>Nein</td></tr><tr><td>Rechner3</td><td>Ja</td></tr><tr><td>Rechner aus dem Internet</td><td>Nein</td></tr></tbody></table></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="firewall-full-rulesets-rulesets-actions"></a>35.2.4. Die Aktionen</h3></div></div></div><p>Die Aktionen im &Uuml;berblick:</p><div class="informaltable"><table border="1"><colgroup><col><col></colgroup><thead><tr><th>Aktion</th><th>Beschreibung</th></tr></thead><tbody><tr><td>Accept</td><td>Paket durchlassen.</td></tr><tr><td>Deny</td><td>Paket verwerfen, der Absender bekommt keine explizite Fehlermeldung (muss auf
                Timeout warten).</td></tr><tr><td>Reject</td><td>Paket verwerfen, zus&auml;tzlich dem Absender eine Fehlermeldung senden (ICMP Port
                unreachable).</td></tr><tr><td>Nothing</td><td>Nichts tun, Paket durchl&auml;uft die weiteren Regeln. Die Log-Option wird dennoch
                ausgef&uuml;hrt.</td></tr><tr><td>Weiterleiten an</td><td>Weiterleitung an eine andere Regelliste; Weiterleitung ist nur an vollst&auml;ndige
                Regellisten gleichen Typs m&ouml;glich.</td></tr><tr><td>Return</td><td>R&uuml;cksprung an urspr&uuml;ngliche Regelliste. Wurde keine Weiterleitung verwendet, ist
                dies gleichbedeutend mit &#8222;Deny&#8220;.</td></tr><tr><td>Transproxy</td><td>Umleitung auf den HTTP-Proxy des Intranators (nur bei Typ &#8222;LAN, Fernzugriff und
                VPN&#8220;). Regeln f&uuml;r den transparenten Proxy m&uuml;ssen immer an Anfang einer Regelliste
                stehen.</td></tr></tbody></table></div><p>Wir empfehlen f&uuml;r das Blocken von Paketen aus dem LAN &#8222;Reject&#8220; zu verwenden. Der Vorteil
        gegen&uuml;ber &#8222;Deny&#8220; ist, dass der Benutzer sofort eine Fehlermeldung bekommt und nicht erst auf
        einen Timeout warten muss.</p><p>F&uuml;r Pakete aus dem Internet (in einer Provider-Regel) empfehlen wir dagegen &#8222;Deny&#8220;,
        denn die sofortigen R&uuml;ckmeldungen von &#8222;Reject&#8220; beschleunigen und vereinfachen einen Portscan aus
        dem Internet erheblich.</p></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="firewall-full-rulesets-rulesets-extra"></a>35.2.5. Extra-Optionen</h3></div></div></div><p>Auf der Karteikarte &#8222;Extra&#8220; sind noch weitere Bedingungen untergebracht.</p><div class="sect3" lang="de"><div class="titlepage"><div><div><h4 class="title"><a name="firewall-full-rulesets-rulesets-extra-time"></a>35.2.5.1. Zeitprofile</h4></div></div></div><p>Sie k&ouml;nnen unter
          Netzwerk&nbsp;&gt;&nbsp;Firewall&nbsp;&gt;&nbsp;Zeiten Zeitprofile
          definieren. Diese Zeitprofile k&ouml;nnen dann bei jeder Regel als Bedingung hinzugef&uuml;gt
          werden. Nur innerhalb des definierten Zeitprofils trifft die Bedingung zu; nur dann kann
          die Aktion ausgef&uuml;hrt werden.</p></div><div class="sect3" lang="de"><div class="titlepage"><div><div><h4 class="title"><a name="firewall-full-rulesets-rulesets-extra-log"></a>35.2.5.2. Logging</h4></div></div></div><p>Logging ist keine Bedingung, sondern wie eine weitere Aktion: Ist das Logging aktiv
          und alle Bedingungen treffen zu, dann wird die Daten des Pakets plus der in der Regeln
          angegebene Logging-Text in der messages-Logdatei protokolliert.</p></div><div class="sect3" lang="de"><div class="titlepage"><div><div><h4 class="title"><a name="firewall-full-rulesets-rulesets-extra-limit"></a>35.2.5.3. Limitierung</h4></div></div></div><p>Limits k&ouml;nnen f&uuml;r die Aktion und f&uuml;r das Logging separat konfiguriert werden. Eine
          Limitierung f&uuml;r die Aktion bedeutet, dass die Aktion nicht ausgef&uuml;hrt wird, sobald das
          Limit &uuml;berschritten wurde. Eine Limitierung f&uuml;r das Log bedeutet, dass das Paket nicht
          protokolliert wird, sobald das Limit &uuml;berschritten wurde.</p><p>Limitiert werden kann auf eine bestimmte Anzahl von Paketen pro Zeiteinheit. &Uuml;ber den
          Spitzenwert kann das Limit kurzfristig &uuml;berschritten werden. Wurde in einer Zeiteinheit
          der Spitzenwert ausgenutzt, steht er in den folgenden Zeiteinheiten erst wieder zur
          Verf&uuml;gung, wenn zwischendurch das Limit in einer Zeiteinheit nicht ausgenutzt
        wurde.</p></div><div class="sect3" lang="de"><div class="titlepage"><div><div><h4 class="title"><a name="firewall-full-rulesets-rulesets-extra-size"></a>35.2.5.4. Paketgr&ouml;&szlig;e</h4></div></div></div><p>Eine Bedingung, die zutrifft, sobald das Paket eine Gr&ouml;&szlig;e in dem angegebenen Bereich
          hat.</p></div><div class="sect3" lang="de"><div class="titlepage"><div><div><h4 class="title"><a name="firewall-full-rulesets-rulesets-extra-state"></a>35.2.5.5. Verbindungsstatus</h4></div></div></div><p>Der Intranator verwendet eine stateful Firewall. Das bedeutet, er ordnet jedes Paket
          einer Verbindung zu und kann sich f&uuml;r jede dieser Verbindungen den Zustand merken. &Uuml;ber
          die Bedingung Verbindungsstatus kann man auf diese Daten zugreifen.</p><div class="informaltable"><table border="1"><colgroup><col><col></colgroup><tbody><tr><td>Neu</td><td>Erstes Paket, das eine neue Verbindung aufbaut</td></tr><tr><td>Ung&uuml;ltig</td><td>Das Paket setzt entweder eine bestehende Verbindung voraus, die nicht
                  existiert, oder passt nicht zu einem bestehenden Verbindungsstatus</td></tr><tr><td>Aufgebaut</td><td>Das Paket geh&ouml;rt zu einer bereits bestehenden Verbindung</td></tr><tr><td>Zugeh&ouml;rig</td><td>Die Verbindung dieses Pakets geh&ouml;rt logisch zu einer anderen, bereits
                  bestehenden Verbindung (z.B. Pakete von ftp-data sind zugeh&ouml;rig zu
                ftp-control)</td></tr><tr><td>Portforwarding</td><td>Die Verbindung des Pakets wird &uuml;ber Portforwarding weitergeleitet</td></tr><tr><td>Statische NAT</td><td>Die Verbindung des Pakets wird &uuml;ber statische NAT weitergeleitet</td></tr></tbody></table></div></div><div class="sect3" lang="de"><div class="titlepage"><div><div><h4 class="title"><a name="firewall-full-rulesets-rulesets-extra-tcpflag"></a>35.2.5.6. TCP-Flags</h4></div></div></div><p>Diese Bedingung wird normalerweise nicht ben&ouml;tigt, der Verbindungsstatus bietet mehr
          M&ouml;glichkeiten.</p></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="firewall-full-rulesets-rulesets-provider"></a>35.2.6. Besonderheiten bei Provider-Regellisten</h3></div></div></div><p>Einige Server (vor allem &ouml;ffentliche FTP-Server) versuchen bei einem Verbindungsaufbau
        Benutzerdaten &uuml;ber das ident-Protokoll zu ermitteln. Dazu baut der Server eine Verbindung zu
        TCP-Port 113 des aufrufenden Clients auf. Wegen NAT landet dieser Aufruf normalerweise beim
        Intranator und wird durch die Provider-Regel blockiert.</p><p>Die meisten dieser Server warten aber auf einen Timeout oder eine Fehlermeldung vom
        ident, bevor sie einen Login erlauben. Daher hat es sich bew&auml;hrt, in jede Providerregel ein
        &#8222;Reject&#8220; f&uuml;r das ident-Protokoll einzuf&uuml;gen.</p><a class="indexterm" name="d0e11518"></a></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="firewall-full-rulesets.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="firewall-full-rulesets.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="firewall-additional-functions.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">35. Kapitel - Vollst&auml;ndige Regellisten&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;36. Kapitel - Weitere Funktionen</td></tr></table></div>
      
    <!-- content end -->
    </div>

  <!-- footer start -->

</div> <!-- close content <div> -->
</div> <!-- close page <div> -->

<div id="sitemap">

<div id="sitemapcol1">
	<a href="../../../produkte/index.php" class="sitemapheader">Produkte</a>
	<ul class="sitemap">
	<li><a href="../../../produkte/intranator.php">Intra2net Business Server</a></li>
	<li><a href="../../../produkte/security_gateway.php">Intra2net Security Gateway</a></li>
	<li><a href="../../../produkte/network_security.php">Intra2net Network Security</a></li>
	<li><a href="../../../produkte/appliance_eco.php">Intra2net Appliance Eco</a></li>
	<li><a href="../../../produkte/appliance_pro.php">Intra2net Appliance Pro</a></li>
	<li><a href="../../../produkte/appliance_ultimate.php">Intra2net Appliance Ultimate</a></li>
	</ul>
</div>

<div id="sitemapcol2">
	<a href="../../../download/index.php" class="sitemapheader">Download</a>
	<ul class="sitemap">
	<li><a href="../../../download/index.php">Software</a></li>
	<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
	<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
	</ul>
</div>

<div id="sitemapcol3">
	<a href="../../index.php" class="sitemapheader">Support</a>
	<ul class="sitemap">
	<li><a href="../../anfrage.php">Support-Anfrage</a></li>
	<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
	<li><a href="http://forum.intra2net.com/">Forum</a></li>
	<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
	<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
	<li><a href="../../schulung.php">Schulung</a></li>
	<li><a href="../../fernwartung.php">Fernwartung</a></li>
	</ul>
</div>

<div id="sitemapcol4">
	<a href="../../../kaufen/index.php" class="sitemapheader">Kaufen</a>
	<ul class="sitemap">
	<li><a href="../../../kaufen/index.php">Partner finden</a></li>
	<li><a href="../../../partner-werden">Partner werden</a></li>
	<li><a href="https://partner.intra2net.com/">Partnerweb</a></li>
	</ul>
</div>

<div id="sitemapcol5">
	<a href="../../../unternehmen/index.php" class="sitemapheader">Unternehmen</a>
	<ul class="sitemap">
	<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
	<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
	<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
	<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
	</ul>
</div>

</div> <!-- close sitemap <div> -->


<div id="footnote">
	<div id="footnotecompany">

		&copy; Intra2net AG 2015
	</div>

	<div id="footnotelinks">
		<a href="../../../impressum.php">Impressum</a>
		<a href="../../../../en/developer/index.html">Entwickler</a>
		<a href="../../../datenschutz.php">Datenschutz</a>
		<a href="../../../unternehmen/kontakt.php">Kontakt</a>
	</div>
</div>

<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-151599-1']);
  _gaq.push(['_gat._anonymizeIp'])
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>

<!-- PHP error counter: 0 -->

<!-- footer end -->

    </body></html>