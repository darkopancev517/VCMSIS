<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>E-Mail-Filter | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="base-email.php" title="15. Kapitel - E-Mail"><link rel="prev" href="base-email-process.php" title="15.6. E-Mail-Verarbeitung"><link rel="next" href="base-email-archiving.php" title="15.8. Archivierung">
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

<a href="base-email-filter.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="base-email-filter.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">15.7. E-Mail-Filter</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="base-email-process.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">15. Kapitel - E-Mail</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="base-email-archiving.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="base-email-filter"></a>15.7. E-Mail-Filter</h2></div></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-email-filter-spam"></a>15.7.1. Spamfilter</h3></div></div></div><div class="sect3" lang="de"><div class="titlepage"><div><div><h4 class="title"><a name="base-email-filter-spam-smtp"></a>15.7.1.1. SMTP-Filterung</h4></div></div></div><a class="indexterm" name="base-email-filter-spam-smtp1"></a><a class="indexterm" name="base-email-filter-spam-smtp2"></a><p>Empfangen Sie Ihre E-Mails direkt per SMTP, k&ouml;nnen Sie als erste Stufe zur
          Spamfilterung E-Mails von bekannten Spamversendern gleich vor der Annahme ablehnen lassen.
          Dies reduziert die Last auf dem System und vermeidet unn&ouml;tigen Datentransfer.</p><p>Ist die Option <span class="guimenuitem">IPs via DNS auf SMTP-Ebene &uuml;berpr&uuml;fen</span> im
          Men&uuml; Dienste&nbsp;&gt;&nbsp;E-Mailfilter&nbsp;&gt;&nbsp;Spam&nbsp;&gt;&nbsp;Einstellungen
          aktiv, so wird die IP jedes Servers, der E-Mails direkt per SMTP einliefern will, per DNS
          &uuml;berpr&uuml;ft. Dabei werden mehrere Blocklisten abgefragt. Ist die IP auf mehreren Blocklisten
          gleichzeitig als Spamversender gef&uuml;hrt, wird der E-Mail-Empfang von diesem Server generell
          abgelehnt. </p><p>Ist die IP des sendenden Servers nur auf wenigen oder gar keiner Blockliste enthalten,
          wird die E-Mail angenommen und durch die weiteren Stufen des Spamfilters eingehend
          gepr&uuml;ft.</p><a class="indexterm" name="d0e4174"></a><a class="indexterm" name="d0e4175"></a></div><div class="sect3" lang="de"><div class="titlepage"><div><div><h4 class="title"><a name="base-email-filter-spam-marking"></a>15.7.1.2. Markierung</h4></div></div></div><a class="indexterm" name="base-email-filter-spam-marking1"></a><a class="indexterm" name="base-email-filter-spam-marking2"></a><p>Der Intranator enth&auml;lt einen mehrstufigen Spamfilter. Dabei wird eine E-Mail sowohl
          durch Spam-typische Kriterien (spezielle Worte, viele Ausrufezeichen, ung&uuml;ltige
          Absenderadressen usw.) als auch durch einen bayesischen Wortfilter kategorisiert. Der
          bayesische Wortfilter kann durch Vergleiche von Wortkombinationen mit einer vortrainierten
          Wortbasis eine Spam-Wahrscheinlichkeit errechnen.</p><p>Zus&auml;tzlich k&ouml;nnen noch DNS-basierte Netzwerktests durchgef&uuml;hrt werden. Dabei wird
          &uuml;berpr&uuml;ft, ob die in der E-Mail enthaltenen E-Mailadressen und URLs in verschiedenen
          Blacklists vorkommen. Da diese &Uuml;berpr&uuml;fung auch f&uuml;r jede interne E-Mail ausgef&uuml;hrt wird,
          sollten Sie diese Option nur aktivieren, wenn Ihre Internetverbindung nicht pro
          Zeiteinheit oder Einwahlversuch abgerechnet wird.</p><p>Des Weiteren kann der Intranator E-Mails auch &uuml;ber das Razor Netzwerk &uuml;berpr&uuml;fen. Das
          Razor Netzwerk ist ein Zusammenschluss von E-Mail-Empf&auml;ngern. Im Razor-Netzwerk werden
          Spam-E-Mails von Hand als Spam markiert. Diese Information wird dann &uuml;ber das
          Razor-Netzwerk verteilt. Je mehr Leute eine E-Mail als Spam einstufen, desto schneller
          wird sie herausgefiltert.</p><p>Ist der Spamfilter aktiviert (unter
          Dienste&nbsp;&gt;&nbsp;E-Mailfilter&nbsp;&gt;&nbsp;Spam&nbsp;&gt;&nbsp;Einstellungen),
          wird f&uuml;r jede E-Mail ein Spam-Punktwert ermittelt und dieser in einem speziellen
          E-Mail-Header abgelegt. Dadurch wird aber noch keine E-Mail gel&ouml;scht oder verschoben. Der
          Punktwert wird in dem Header &#8222;X-Spam-Level:&#8220; abgelegt. Er errechnet sich durch
          (Spampunkte+100)*10. Dadurch ist der Wert immer positiv und ganzzahlig, was einen
          Vergleich f&uuml;r die meisten anderen Programme erst erm&ouml;glicht. Au&szlig;erdem wird eine
          ausf&uuml;hrliche Beschreibung, warum eine E-Mail Spam ist oder nicht, im &#8222;X-Spam-Status:&#8220;
          Header abgelegt.</p><a class="indexterm" name="d0e4199"></a><a class="indexterm" name="d0e4200"></a></div><div class="sect3" lang="de"><div class="titlepage"><div><div><h4 class="title"><a name="base-email-filter-spam-levels"></a>15.7.1.3. Schwellwerte</h4></div></div></div><a class="indexterm" name="base-email-filter-spam-levels1"></a><a class="indexterm" name="base-email-filter-spam-levels2"></a><a class="indexterm" name="base-email-filter-spam-levels3"></a><a class="indexterm" name="base-email-filter-spam-levels4"></a><p>Je h&ouml;her der Spam-Punktwert ist, desto h&ouml;her ist die Wahrscheinlichkeit, dass es sich
          um Spam handelt. Werte kleiner als 4 weisen normalerweise auf erw&uuml;nschte E-Mails hin. Bei
          Werten zwischen 5 und 8 ist die Wahrscheinlichkeit f&uuml;r Spam h&ouml;her, es kann sich aber
          dennoch um eine erw&uuml;nschte E-Mail handeln. Bei Werten von 8 und gr&ouml;&szlig;er ist die E-Mail
          ziemlich sicher Spam.</p><p>Je niedriger der Schwellwert, desto mehr E-Mails werden rausgefiltert. Gleichzeitig
          steigt aber auch die Gefahr, dass eine wichtige E-Mail im Spam-Ordner landet.</p><p>Im Intranator wird daher typischerweise zwischen 3 Kategorien unterschieden:
          erw&uuml;nschte E-Mail, Spamverdacht und Spam.</p><p>Der Spamverdacht ist f&uuml;r E-Mails gedacht, die zwar klare Spam-Merkmale aufweisen, aber
          nicht ganz eindeutig als Spam klassifiziert werden k&ouml;nnen. Es empfiehlt sich, diese
          E-Mails regelm&auml;&szlig;ig (z.B. einmal pro Woche) manuell zu &uuml;berpr&uuml;fen.</p><p>Spam sind E-Mails, die eindeutig als Spam erkannt wurden. Diese E-Mails m&uuml;ssen
          normalerweise nicht manuell kontrolliert werden. F&uuml;r den Fall von Fehlkonfigurationen
          empfiehlt es sich aber dennoch, diese E-Mails nicht sofort zu l&ouml;schen sondern f&uuml;r einige
          Tage aufzubewahren.</p><p>Als guten Kompromiss haben sich die Schwellwerte 5 f&uuml;r Spamverdacht und 8 f&uuml;r Spam
          herausgestellt.</p><a class="indexterm" name="d0e4240"></a><a class="indexterm" name="d0e4241"></a><a class="indexterm" name="d0e4242"></a><a class="indexterm" name="d0e4243"></a></div><div class="sect3" lang="de"><div class="titlepage"><div><div><h4 class="title"><a name="base-email-filter-spam-global"></a>15.7.1.4. Globaler Spamfilter</h4></div></div></div><a class="indexterm" name="base-email-filter-spam-global1"></a><a class="indexterm" name="base-email-filter-spam-global2"></a><p>Unter Dienste&nbsp;&gt;&nbsp;E-Mailfilter&nbsp;&gt;&nbsp;Spam&nbsp;&gt;&nbsp;Global
          kann der globale Spamfilter aktiviert werden. Er filtert alle empfangenen E-Mails -
          unabh&auml;ngig davon, ob sie an einen lokalen Benutzer gehen oder weitergeleitet werden. Daher
          empfehlen wir den Globalen Spamfilter vor allem f&uuml;r die F&auml;lle, in denen die E-Mails nicht
          endg&uuml;ltig auf dem Intranator abgelegt, sondern an einen anderen Server weitergeleitet
          werden.</p><div class="sect4" lang="de"><div class="titlepage"><div><div><h5 class="title"><a name="base-email-filter-spam-global-actions"></a>15.7.1.4.1. Aktionen</h5></div></div></div><p>Die folgenden Filteraktionen sind jeweils f&uuml;r Spam und Spamverdacht separat
            konfigurierbar. Damit k&ouml;nnen die Kategorien Spamverdacht und Spam unterschiedlich
            behandelt werden.</p><p>Die Option <span class="guimenuitem">E-Mail-Betreff ver&auml;ndern</span> sorgt daf&uuml;r, dass
            jeder betroffenen E-Mail &#8222;***SPAM***&#8220; bzw. &#8222;***SPAMVERDACHT***&#8220; im Betreff vorangestellt
            wird. Dies macht vor allem Sinn, wenn die E-Mails normal zugestellt werden.</p><p>Bei <span class="guimenuitem">normal zustellen</span> gehen die betroffenen E-Mails
            weiterhin ihren normalen Weg und werden nicht gestoppt oder umgeleitet. Dies ist vor
            allem im Zusammenhang mit dem Ver&auml;ndern des Betreffs und einer Filterregel auf dem
            Zielserver sinnvoll. Die Filterregel auf dem Zielserver kann die E-Mails dann anhand des
            Betreffs in entsprechende Unterordner ablegen.</p><p>Mit der Option <span class="guimenuitem">umleiten</span> werden die betroffenen E-Mails an
            eine Sammeladresse umgeleitet. Wenn Sie hierf&uuml;r ein Konto auf dem Intranator selber
            verwenden, achten Sie unbedingt darauf, dort den benutzerabh&auml;ngigen Spamfilter zu
            aktivieren und die Spam-E-Mails automatisch nach einiger Zeit l&ouml;schen zu lassen.
            Ansonsten besteht die Gefahr, dass das Spam-Konto unbegrenzt w&auml;chst.</p></div><div class="sect4" lang="de"><div class="titlepage"><div><div><h5 class="title"><a name="base-email-filter-spam-global-quarantine"></a>15.7.1.4.2. Quarant&auml;ne</h5></div></div></div><a class="indexterm" name="base-email-filter-spam-global-quarantine1"></a><a class="indexterm" name="base-email-filter-spam-global-quarantine2"></a><p>Die Spam-Quarant&auml;ne nimmt erkannte Spam-E-Mails auf, h&auml;lt sie f&uuml;r eine einstellbare
            Zeit bereit und l&ouml;scht sie dann. Bei Bedarf k&ouml;nnen falsch erkannte E-Mails aus der
            Quarant&auml;ne wieder freigegeben und normal zugestellt werden.</p><p>Die Spam-Quarant&auml;ne selbst ist unter
            Dienste&nbsp;&gt;&nbsp;E-Mailfilter&nbsp;&gt;&nbsp;Quarant&auml;ne&nbsp;&gt;&nbsp;Spam
            erreichbar. Sie enth&auml;lt die erkannten Spam-E-Mails aller Empf&auml;nger zusammen. Daher ist
            sie normalerweise nur f&uuml;r Benutzer mit administrativen Rechten erreichbar. Sie kann auch
            zus&auml;tzlich mit einem Datenschutz-Passwort unter Information&nbsp;&gt;&nbsp;Datenschutz
            nur im 4-Augen-Verfahren zug&auml;nglich gemacht werden.</p><p>Um jedem Empf&auml;nger selbst einen &Uuml;berblick &uuml;ber seine gefilterten E-Mails zu geben,
            gibt es die Report-Funktion. Wenn aktiviert, bekommt jeder Empf&auml;nger zu den
            einstellbaren Versandzeiten automatisch eine E-Mail mit einer &Uuml;bersicht &uuml;ber die
            gefilterten E-Mails.</p><p>In der Report-E-Mail befindet sich unter den Daten zu jeder gefilterten E-Mail ein
            Link, mit dem die entsprechende E-Mail aus der Quarant&auml;ne freigegeben werden kann. Die
            Report-E-Mails sind nach aufsteigender Spam-Wahrscheinlichkeit sortiert.</p><div class="note" style="margin-left: 0.2in; margin-right: 0.5in;"><table border="0" summary="Note"><tr><td rowspan="2" align="center" valign="top" width="25"><img alt="[Hinweis]" src="../images/admon/note.png"></td><th align="left">Hinweis</th></tr><tr><td align="left" valign="top"><p>Da die Report-E-Mails die Betreff-Zeilen der gefilterten E-Mails enthalten, kann
              es sein, dass ein zus&auml;tzlich auf dem Zielserver oder Client installierter Spamfilter
              die Report-E-Mails f&auml;lschlicherweise als Spam identifiziert.</p><p>Setzen Sie einen zus&auml;tzlichen Spamfilter ein, sollten Sie daher die
              Postmasteradresse des Intranators (Men&uuml;
              Dienste&nbsp;&gt;&nbsp;E-Mail&nbsp;&gt;&nbsp;Einstellungen) dort in die Whitelist
              eintragen. Die Postmasteradresse des Intranators wird f&uuml;r die Reports als
              Absenderadresse verwendet.</p></td></tr></table></div><a class="indexterm" name="d0e4309"></a><a class="indexterm" name="d0e4310"></a><a class="indexterm" name="d0e4311"></a><a class="indexterm" name="d0e4312"></a></div></div><div class="sect3" lang="de"><div class="titlepage"><div><div><h4 class="title"><a name="base-email-filter-spam-user"></a>15.7.1.5. Benutzerabh&auml;ngiger Spamfilter</h4></div></div></div><a class="indexterm" name="base-email-filter-spam-user1"></a><a class="indexterm" name="base-email-filter-spam-user2"></a><p>Der benutzerabh&auml;ngige Spamfilter kann f&uuml;r jeden Benutzer auf dem Intranator
          individuell konfiguriert werden. Er ist in der Lage, erkannte Spam-E-Mails in speziellen
          IMAP-Unterordnern des Benutzers abzulegen. Wir empfehlen den Einsatz des
          benutzerabh&auml;ngigen Spamfilters daher f&uuml;r die F&auml;lle, in denen die E-Mails endg&uuml;ltig auf dem
          Intranator abgelegt werden.</p><p>Erreicht eine E-Mail einen Benutzer, der unter
          Benutzermanager&nbsp;&gt;&nbsp;Benutzer&nbsp;:&nbsp;Spamfilter den Spamfilter f&uuml;r sich
          aktiviert hat, wird die E-Mail &uuml;berpr&uuml;ft. Der Benutzer-Spamfilter ist zweistufig
          aufgebaut. Es gibt einen Schwellwert f&uuml;r spamverd&auml;chtige E-Mails sowie einen f&uuml;r
          &#8222;richtigen&#8220; Spam. Hat die E-Mail einen Spam-Punktwert gr&ouml;&szlig;er oder gleich dem eingetragenen
          Schwellwert wird sie nicht gel&ouml;scht, sondern in die IMAP Unterordner &#8222;Spamverdacht&#8220; oder
          &#8222;Spam&#8220; des Benutzers abgelegt. Auf Wunsch k&ouml;nnen Spam-E-Mails auch an eine zentrale
          Sammeladresse weitergeleitet werden.</p><p>Jeder Benutzer hat zus&auml;tzlich noch die M&ouml;glichkeit, dies durch Blacklists (Alle diese
          Absender oder Empf&auml;nger sind immer Spam) und Whitelists (Alle diese Absender oder
          Empf&auml;nger sind nie Spam) zu beeinflussen.</p><p> Wenn ein Benutzer per IMAP auf seine E-Mails zugreift, sind die Unterordner direkt
          sichtbar. Eventuell muss die Ordnerliste im E-Mail-Programm neu &uuml;bertragen und die Ordner
          abonniert werden (subscribe). Beim Zugriff via POP3 bleiben die Spam-E-Mails auf dem
          Server. Der Benutzer sollte daher den &#8222;Spamverdacht&#8220;-Ordner regelm&auml;&szlig;ig per Webmail auf
          f&auml;lschlich gefilterte Nachrichten &uuml;berpr&uuml;fen.</p><a class="indexterm" name="d0e4336"></a><a class="indexterm" name="d0e4337"></a></div><div class="sect3" lang="de"><div class="titlepage"><div><div><h4 class="title"><a name="base-email-filter-spam-trusted-servers"></a>15.7.1.6. Glaubw&uuml;rdige Server</h4></div></div></div><a class="indexterm" name="base-email-filter-spam-trusted-servers1"></a><a class="indexterm" name="base-email-filter-spam-trusted-servers2"></a><p>Im Standardmodus pr&uuml;ft der Spamfilter bei allen &#8222;Received&#8220;-Kopfzeilen einer E-Mail, ob
          deren IPs in DNS-Blacklisten enthalten sind. Im optimierten Modus wird nur die IP des
          letzten Servers des Versenders &uuml;berpr&uuml;ft. Dadurch wird die Spam-Erkennungsrate weiter
          gesteigert sowie die potentielle Falscherkennung von erw&uuml;nschten Nachrichten reduziert.
          Der aktuell verwendete Modus ist unter
            <span class="guimenu">Dienste&nbsp;&gt;&nbsp;E-Mailfilter&nbsp;&gt;&nbsp;Spam&nbsp;&gt;&nbsp;Glaubw&uuml;rdige
            Server</span> einsehbar.</p><p>Um die IP des letzten Versender-Servers von gef&auml;lschten Daten unterscheiden zu k&ouml;nnen,
          muss das System wissen, welche Server glaubw&uuml;rdig sind. Ein SMTP-Server gilt als
          glaubw&uuml;rdig, wenn angenommen werden kann, dass dieser die Received-Zeilen im E-Mail-Header
          nicht verf&auml;lscht und seinen eigenen Received-Eintrag wahrheitsgem&auml;&szlig; einf&uuml;gt. Man kann
          normalerweise davon ausgehen, dass alle f&uuml;r Empfang und Verarbeitung der eigenen E-Mails
          konfigurierten Server glaubw&uuml;rdig sind, da deren Betreiber vertraglich gebunden sind. </p><p>Der Intranator versucht automatisch die glaubw&uuml;rdigen Server zu ermitteln, dabei kommt
          f&uuml;r jede E-Mail-Empfangsmethode ein angepasstes Verfahren zum Einsatz.</p><p><b>Glaubw&uuml;rdige Server bei direktem SMTP und POP-Sammelkonten (Multidrop).&nbsp;</b>Der Intranator fragt automatisch per DNS f&uuml;r jede konfigurierte Domain die f&uuml;r den
            E-Mail-Empfang zust&auml;ndigen Server (MX-Eintrag der Domain) ab. Diese Server werden der
            Liste der glaubw&uuml;rdigen Server hinzugef&uuml;gt.</p><p>In folgenden F&auml;llen kann es notwendig sein, die Liste der glaubw&uuml;rdigen Server
          anzupassen: </p><div class="orderedlist"><ol type="1"><li><p>Die E-Mails werden beim f&uuml;r den E-Mail-Empfang zust&auml;ndigen Server (MX-Eintrag
                der Domain) entgegengenommen und dann an einen anderen Server weitergeleitet (z.B.
                zur &Uuml;berpr&uuml;fung oder Zwischenspeicherung), bevor Sie zum Intranator gehen. Hier
                m&uuml;ssen die IPs oder DNS-Namen aller Zwischenserver in die Liste der &#8222;weiteren
                glaubw&uuml;rdigen Server&#8220; eingetragen werden.</p></li><li><p>Der Intranator bekommt per DNS im lokalen Netz andere Daten f&uuml;r die eigene
                Domain zu sehen, als es &#8222;drau&szlig;en&#8220; im Internet der Fall ist. Diese Konstellation wird
                normalerweise &#8222;Split-DNS&#8220; genannt. Hier m&uuml;ssen die IPs aller extern f&uuml;r den
                E-Mail-Empfang zust&auml;ndigen Server (MX-Eintrag der Domain) in die Liste der &#8222;weiteren
                glaubw&uuml;rdigen Server&#8220; eingetragen werden.</p></li><li><p>Die E-Mails werden von einem Server unter der Domain A empfangen, dort auf die
                Domain B umgeschrieben und dann an den Intranator oder f&uuml;r die Domain B zust&auml;ndigen
                Server weitergeleitet. Der Intranator kennt nur die Domain B. Hier muss die
                urspr&uuml;ngliche Domain A in die Liste der &#8222;glaubw&uuml;rdigen Domains&#8220; aufgenommen
                werden.</p></li></ol></div><p>
        </p><p><b>Glaubw&uuml;rdige Server bei einzelnen POP-Konten.&nbsp;</b>Der Intranator &uuml;berpr&uuml;ft automatisch per DNS alle unter
            Dienste&nbsp;&gt;&nbsp;E-Mail&nbsp;&gt;&nbsp;Abholen eingetragenen E-Mail-Server. Diese
            Server werden als glaubw&uuml;rdig behandelt. Zus&auml;tzlich wird jeder Servername auf die
            Second-Level-Domain gek&uuml;rzt, so wird z.B. aus dem Servernamen &#8222;pop.1und1.de&#8220; die Domain
            &#8222;1und1.de&#8220;. Die f&uuml;r diese Domain zust&auml;ndigen E-Mail-Server (MX-Eintr&auml;ge) werden
            abgefragt und zus&auml;tzlich als glaubw&uuml;rdige Server &uuml;bernommen.</p><p>In folgenden F&auml;llen kann es notwenig sein, die Liste der glaubw&uuml;rdigen Server
          anzupassen: </p><div class="orderedlist"><ol type="1"><li><p>Der Provider verwendet f&uuml;r seine eigenen E-Mails andere Server als f&uuml;r die
                E-Mails der Kunden. Tragen Sie in diesem Fall die Domains aller E-Mail-Adressen, die
                bei Ihnen verwendet werden, in die Liste der &#8222;glaubw&uuml;rdigen Domains&#8220; ein. </p></li><li><p>Beim Provider werden die E-Mails auf einem Server empfangen, z.B. zur
                &Uuml;berpr&uuml;fung an einen anderen Server weitergeleitet und dann nochmal auf einem
                anderen Server zur Abholung bereitgehalten. In diesem Fall m&uuml;ssen Sie die IPs oder
                DNS-Namen aller zur &Uuml;berpr&uuml;fung verwendeten Zwischenserver in die Liste der
                &#8222;weiteren glaubw&uuml;rdigen Server&#8220; eintragen.</p></li><li><p>E-Mails werden von einer Domain empfangen und dort automatisiert an eine andere
                Domain weitergeleitet. Der Intranator holt dann die weitergeleiteten E-Mails ab.
                Tragen Sie in diesem Fall alle urspr&uuml;nglichen Domains, von denen aus weitergeleitet
                wird, in die Liste der &#8222;glaubw&uuml;rdigen Domains&#8220; ein.</p></li></ol></div><p>
        </p><p>Anhand der letzten 1.000 Spam-E-Mails kann der Intranator erkennen, ob die Liste der
          glaubw&uuml;rdigen Server korrekt ist. Nach dieser Kalibrierung schaltet der Spamfilter, falls
          m&ouml;glich, in den optimierten Modus. Die Kalibrierung wird im laufenden Betrieb st&uuml;ndlich
          erneut &uuml;berpr&uuml;ft.</p><div class="note" style="margin-left: 0.2in; margin-right: 0.5in;"><table border="0" summary="Note"><tr><td rowspan="2" align="center" valign="top" width="25"><img alt="[Hinweis]" src="../images/admon/note.png"></td><th align="left">Hinweis</th></tr><tr><td align="left" valign="top"><p>Nach &Auml;nderung der glaubw&uuml;rdigen Server oder Domains werden bis zu 1.000
            Spam-Nachrichten ben&ouml;tigt, bevor der Spamfilter automatisch in den optimierten Modus
            wechselt.</p></td></tr></table></div><a class="indexterm" name="d0e4405"></a><a class="indexterm" name="d0e4406"></a></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-email-filter-virus"></a>15.7.2. Virenscanner</h3></div></div></div><a class="indexterm" name="base-email-filter-virus1"></a><a class="indexterm" name="base-email-filter-virus2"></a><a class="indexterm" name="base-email-filter-virus3"></a><p>Unter Dienste&nbsp;&gt;&nbsp;E-Mailfilter&nbsp;&gt;&nbsp;Antivirus kann der
        E-Mail-Virenscanner aktiviert werden. Ist er aktiviert, werden alle E-Mails, die den
        Intranator passieren (eingehend, ausgehend, weitergeleitet,...), auf Viren &uuml;berpr&uuml;ft.</p><p>Wurde ein Virus gefunden, so wird er unter
        Dienste&nbsp;&gt;&nbsp;E-Mailfilter&nbsp;&gt;&nbsp;Quarant&auml;ne&nbsp;:&nbsp;Virus-Quarant&auml;ne
        in Quarant&auml;ne genommen und kann dort vom Administrator inspiziert werden.</p><p>Bei einem gefundenen Virus k&ouml;nnen Warnungen an den Administrator sowie an den Empf&auml;nger
        gesendet werden. Es werden nur Warnungen an lokale Empf&auml;nger versendet.</p><p>Da der F-Secure Virenscanner eine heuristische Virenerkennung unterst&uuml;tzt, werden manche
        Dateien nur als verd&auml;chtig eingestuft. Diese k&ouml;nnen mit der entsprechenden Option auch
        blockiert werden. Sie sollten diese Option nur deaktivieren, falls h&auml;ufiger wichtige Dateien
        falsch erkannt werden.</p><a class="indexterm" name="d0e4433"></a><a class="indexterm" name="d0e4434"></a><a class="indexterm" name="d0e4435"></a></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="base-email-filter-attachment"></a>15.7.3. Anhangfilter</h3></div></div></div><a class="indexterm" name="base-email-filter-attachment1"></a><p>E-Mail-Anh&auml;nge k&ouml;nnen neue, unbekannte Viren enthalten. Diese m&uuml;ssen als ausf&uuml;hrbare
        Dateien auf den PC gelangen. Der Intranator kann E-Mail-Anh&auml;nge untersuchen und bestimmte
        Typen blockieren. So k&ouml;nnen Sie sichergehen, dass keine ausf&uuml;hrbare Datei per E-Mail auf
        einen Rechner im Intranet gelangt.</p><p>Der Anhangfilter untersucht Anh&auml;nge anhand der Dateiendung sowie des MIME-Typs.
        Zus&auml;tzlich f&uuml;hrt er eine Typerkennung auf die tats&auml;chlich in der E-Mail enthaltenen Daten
        durch. Archive wie z.B. ZIP oder RAR werden auch durchsucht. Verschl&uuml;sselte (mit einem
        Passwort gesch&uuml;tzte) Archive k&ouml;nnen vom Anhangfilter nicht untersucht werden. Deswegen ist
        es m&ouml;glich und ratsam, sie generell zu blockieren.</p><p>Auf der Seite
        Dienste&nbsp;&gt;&nbsp;E-Mailfilter&nbsp;&gt;&nbsp;Anhang&nbsp;&gt;&nbsp;Filterlisten k&ouml;nnen
        Sie Filterlisten f&uuml;r Dateianh&auml;nge anlegen. Es wird zwischen Freigabe- und Sperrlisten
        unterschieden. Freigabelisten lassen nur bekannte und freigegebene Anh&auml;nge durch,
        Sperrlisten lassen alles bis auf die aufgef&uuml;hrten Eintr&auml;ge durch.</p><p>Die Filterlisten &#8222;Alles erlaubt&#8220;, &#8222;Alles verboten&#8220; sowie &#8222;Ausf&uuml;hrbare Dateien&#8220; sind
        vordefiniert. Unter
        Dienste&nbsp;&gt;&nbsp;E-Mailfilter&nbsp;&gt;&nbsp;Anhang&nbsp;&gt;&nbsp;Einstellungen legen
        Sie globale Einstellungen zum Anhangfilter sowie die &#8222;Standard-Filterliste&#8220; fest. Bei
        Auslieferung steht sie auf &#8222;Ausf&uuml;hrbare Dateien&#8220;. Ausgehende E-Mails sowie
        Domain-Weiterleitungen werden &uuml;ber diese Standard-Liste gefiltert.</p><p>Eingehende E-Mails verwenden die Filterliste der Benutzergruppen. Diese kann unter
        Benutzermanager&nbsp;&gt;&nbsp;Gruppen&nbsp;:&nbsp;Rechte zugewiesen werden. Standardm&auml;&szlig;ig
        verwenden alle Benutzergruppen die &#8222;Standard-Filterliste&#8220;. Ist ein Benutzer in mehreren
        Gruppen mit unterschiedlichen Filterlisten Mitglied, so werden die Filterlisten gemischt.
        Freigabelisten haben dabei Vorrang vor Sperrlisten. So k&ouml;nnen Sie generell alle ausf&uuml;hrbaren
        Dateien sperren, jedoch z.B. f&uuml;r die Administrator-Gruppe .exe freigeben.</p><p>Wird eine E-Mail gefiltert, so liegt sie unter
        Dienste&nbsp;&gt;&nbsp;E-Mailfilter&nbsp;&gt;&nbsp;Quarant&auml;ne&nbsp;:&nbsp;Anhang in
        Quarant&auml;ne und der Administrator bekommt einen Hinweis. Die E-Mail kann sp&auml;ter per Mausklick
        freigegeben oder gel&ouml;scht werden. Alternativ ist es bei eingehenden E-Mails m&ouml;glich, dass
        die E-Mail ohne den (potentiell gef&auml;hrlichen) Anhang ausgeliefert wird. Die Original-E-Mail
        inkl. Anhang liegt dann in der Quarant&auml;ne und kann bei Bedarf freigegeben werden.</p><a class="indexterm" name="d0e4456"></a></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="base-email-process.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="base-email.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="base-email-archiving.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">15.6. E-Mail-Verarbeitung&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;15.8. Archivierung</td></tr></table></div>
      
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