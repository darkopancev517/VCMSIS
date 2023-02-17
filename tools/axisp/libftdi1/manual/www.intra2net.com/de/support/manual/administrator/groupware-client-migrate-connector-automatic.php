<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Die automatische Migration | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="groupware-client-migrate-connector.php" title="24. Kapitel - Migration vom Intranator Groupware Connector"><link rel="prev" href="groupware-client-migrate-connector.php" title="24. Kapitel - Migration vom Intranator Groupware Connector"><link rel="next" href="groupware-client-migrate-connector-manual.php" title="24.3. Die manuelle Migration">
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

<a href="groupware-client-migrate-connector-automatic.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="groupware-client-migrate-connector-automatic.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">24.2. Die automatische Migration</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="groupware-client-migrate-connector.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">24. Kapitel - Migration vom Intranator Groupware Connector</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="groupware-client-migrate-connector-manual.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="groupware-client-migrate-connector-automatic"></a>24.2. Die automatische Migration</h2></div></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="groupware-client-migrate-connector-automatic-overview"></a>24.2.1. &Uuml;berblick</h3></div></div></div><p>Hier ein grober &Uuml;berblick dar&uuml;ber, wie die automatische Migration vor sich geht.
                Die einzelnen Schritte werden im folgenden Abschnitt ausf&uuml;hrlich erkl&auml;rt.</p><div class="itemizedlist"><ul type="disc"><li><p>Mit Hilfe des alten Groupware Connectors die bestehenden Daten vollst&auml;ndig
                        mit dem Server synchronisieren.</p></li><li><p>Ein Backup der Daten auf Client und Server erstellen.</p></li><li><p>Den alten Groupware Connector deinstallieren, den neuen Intra2net
                        Groupware Client installieren.</p></li><li><p>Ein neues Profil ohne E-Mail-Konto anlegen, eine Datendatei vom Typ
                        Intranator Groupware Client hinzuf&uuml;gen.</p></li><li><p>Die Datendatei des neuen Profils mit der bestehenden Datendatei des
                        Groupware Connectors &uuml;berschreiben.</p></li><li><p>Outlook starten und den Konvertierungs-Assistenten die Konvertierung
                        durchf&uuml;hren lassen.</p></li><li><p>Das Migrationsprofil l&ouml;schen und ein neues Profil anlegen. Die Daten
                        werden automatisch vom Server geladen.</p></li><li><p>Abonnements von Groupwareordnern im direkt von Outlook verwalteten
                        IMAP-Konto aufr&auml;umen; Kontrolle der Freigaben an andere Benutzer.</p></li></ul></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="groupware-client-migrate-connector-automatic-steps"></a>24.2.2. Die Migration in einzelnen Schritten</h3></div></div></div><div class="procedure"><ol type="1"><li><p>&Ouml;ffnen Sie Outlook mit dem Profil des Groupware Connectors. &Ouml;ffnen Sie die
                        KQueue im Infobereich der Tastleiste und lassen sich den Zustand der
                        Warteschlange anzeigen. Die Warteschlange muss leer sein (Anzeige:
                            <code class="computeroutput">0/0</code>), bevor Sie fortfahren
                        k&ouml;nnen.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector01.png"></div></div></li><li><p>Schlie&szlig;en Sie Outlook.</p></li><li><p>Kontrollieren Sie, dass Sie &uuml;ber ein aktuelles Backup der Daten auf dem
                        Intranator Server verf&uuml;gen. Wenn nicht, so holen Sie dies &uuml;ber das Men&uuml;
                            <span class="guimenu">System&nbsp;&gt;&nbsp;Backup&nbsp;&gt;&nbsp;Einstellungen</span>
                        nach und warten, bis auf der Hauptseite nicht mehr angezeigt wird, dass das
                        Backup momentan erstellt wird.</p></li><li><p>Stellen Sie sicher, dass das Konto dieses Benutzers von nun an nicht mehr
                        mit dem Groupware Connector verwendet wird. Dies gilt auch f&uuml;r die
                        Verwendung durch andere Benutzer &uuml;ber freigegebene Ordner.</p></li><li><p>&Ouml;ffnen Sie die Windows-Systemsteuerung, Men&uuml; <span class="guimenu">Programme</span>,
                        bzw. <span class="guimenu">Programme und Funktionen</span>.</p></li><li><p>Markieren Sie den Intranator Groupware Connector und w&auml;hlen
                            <span class="guibutton">Deinstallieren</span>.</p></li><li><p>Im Laufe der Deinstallation werden Sie aufgefordert den Outlook-Dienst
                        des Groupware Connectors zu l&ouml;schen. Markieren Sie den Dienst und klicken
                        auf <span class="guibutton">L&ouml;schen</span>. </p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector02.png"></div></div></li><li><p>Fahren Sie mit der Deinstallation fort, lassen Sie die Datendateien
                        bestehen wie sie sind.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector03.png"></div></div></li><li><p>Installieren Sie nun den Intra2net Groupware Client, falls Sie dies noch
                        nicht getan haben.</p></li><li><p>&Ouml;ffnen Sie die Windows-Systemsteuerung, Men&uuml; <span class="guimenu">E-Mail (32
                            Bit)</span>. Lassen Sie sich die Profile anzeigen.</p></li><li><p>W&auml;hlen Sie das Profil des Groupware Connectors aus und klicken auf
                            <span class="guibutton">Entfernen</span>. </p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector04.png"></div></div></li><li><p>F&uuml;gen Sie ein neues Profil hinzu. Dieses wird nur tempor&auml;r f&uuml;r die
                        Migration verwendet und danach wieder gel&ouml;scht.</p></li><li><p>Geben Sie dem neuen Profil einen Namen, z.B.
                            <strong class="userinput"><code>Migration</code></strong>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector07.png"></div></div></li><li><p>Brechen Sie den Assistenten zur Einrichtung eines Kontos ab und
                        best&auml;tigen, dass Sie ein Profil ohne E-Mail-Konto erstellen m&ouml;chten.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector08.png"></div></div><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector09.png"></div></div></li><li><p>Markieren Sie das neue Profil und klicken auf
                            <span class="guibutton">Eigenschaften</span>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector10.png"></div></div></li><li><p>W&auml;hlen Sie <span class="guibutton">Datendateien</span> und f&uuml;gen eine neue
                        Datendatei hinzu.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector12.png"></div></div></li><li><p>W&auml;hlen Sie als Speichertyp f&uuml;r die neue Datendatei <span class="guilabel">Intranator
                            Groupware Client Datendatei (.mxstore)</span> aus. </p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector13.png"></div></div></li><li><p>W&auml;hlen Sie den Speicherort f&uuml;r die neue Datendatei aus. Merken Sie sich
                        diesen Speicherort, er wird in einem folgenden Schritt ben&ouml;tigt.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector14.png"></div></div></li><li><p>Wenn die neue Datendatei mit dem Namen <span class="guilabel">Groupware
                            Ordner</span> angezeigt wird, k&ouml;nnen Sie die Kontoeinstellungen und
                        die Systemsteuerung schlie&szlig;en.
                        </p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector15.png"></div></div><p>
                    </p></li><li><p>&Ouml;ffnen Sie den Windows-Explorer und dort &uuml;ber das Men&uuml; die
                            <span class="guimenu">Ordner- und Suchoptionen</span>.</p></li><li><p>Schalten Sie die Option <span class="guilabel">Erweiterungen bei bekannten Dateitypen
                            ausblenden</span> ab.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector16.png"></div></div></li><li><p>Lassen Sie ausgeblendete Dateien anzeigen</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector17.png"></div></div></li><li><p>Navigieren Sie zum Speicherort der Outlook-Datendatei des bisherigen
                        Groupware-Connector-Profils. Standardm&auml;&szlig;ig ist diese im Verzeichnis des
                        Benutzers unter <code class="filename">AppData\Roaming\Intra2net</code>, bzw.
                            <code class="filename">Lokale Einstellungen\Anwendungsdaten\Intra2net</code>, zu
                        finden. </p></li><li><p>Klicken Sie die Datei mit Rechts an und w&auml;hlen
                            <span class="guilabel">Kopieren</span>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector18.png"></div></div></li><li><p>Navigieren Sie zum Speicherort, den Sie eben f&uuml;r die Outlook-Datendatei
                        des Intra2net Groupware Clients gew&auml;hlt haben.</p></li><li><p>Klicken Sie mit Rechts in einen leeren Bereich des Fensters und w&auml;hlen
                            <span class="guilabel">Einf&uuml;gen</span>. Damit kopieren Sie die bisherige
                        Datendatei an den neuen Speicherort. Gleichzeitig bleibt am alten
                        Speicherort eine Sicherheitskopie der Datendatei bestehen.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector19.png"></div></div></li><li><p>Klicken Sie die Datendatei des neuen Profils mit Rechts an. Sie erkennen
                        die Datei am Typ <code class="computeroutput">mxstore</code> und dem
                        Dateinamen, der mit dem Namen des Profils beginnt. W&auml;hlen Sie
                            <span class="guilabel">Eigenschaften</span>.</p></li><li><p>Markieren Sie den vollst&auml;ndigen Dateinamen inkl. der Endung .mxstore.
                        Klicken Sie mit Rechts in den Dateinamen und w&auml;hlen
                            <span class="guilabel">Kopieren</span>. Der vollst&auml;ndige Dateiname ist nun in der
                        Zwischenablage.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector20.png"></div></div></li><li><p>L&ouml;schen Sie die Datendatei des neuen Profils.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector21.png"></div></div></li><li><p>Klicken Sie mit Rechts auf die Datendatei des bisherigen Profils und
                        w&auml;hlen <span class="guilabel">Umbenennen</span>.</p></li><li><p>Markieren Sie den vollst&auml;ndigen Dateinamen der Datei, inkl. der Endung
                            <code class="computeroutput">.pst</code>. Sollte die Endung nicht angezeigt
                        werden, m&uuml;ssen Sie Schritt 21 wiederholen.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector22.png"></div></div></li><li><p>&Uuml;berschreiben Sie den Dateinamen der alten Datendatei mit dem Namen der
                        neuen Datendatei. &Uuml;bernehmen Sie dazu den Namen aus der Zwischenablage in
                        dem Sie <span class="keycap"><strong>Strg</strong></span>+<span class="keycap"><strong>V</strong></span> dr&uuml;cken. Damit erh&auml;lt die bisherige Datendatei den Namen der
                        neuen.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector23.png"></div></div></li><li><p>Best&auml;tigen Sie, dass Sie die Dateiendung &auml;ndern m&ouml;chten.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector24.png"></div></div></li><li><p>Starten Sie nun Outlook mit dem neuen Profil.</p></li><li><p>Bei Outlook 2010 erscheint nun ein Assistent zur Konfiguration. Gehen Sie
                        auf <span class="guibutton">Weiter</span> und w&auml;hlen, dass Sie kein E-Mail-Konto
                        konfigurieren m&ouml;chten.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector26.png"></div></div></li><li><p>Best&auml;tigen Sie, dass Sie ohne E-Mail-Unterst&uuml;tzung fortfahren
                        wollen.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector27.png"></div></div></li><li><p>Der Konvertierungsassistent fragt Sie nun schrittweise, ob Sie die n&ouml;tigen
                        Voraussetzungen f&uuml;r die Konvertierung aus den vorigen Schritten geschaffen
                        haben. Starten Sie die Konvertierung, wenn Sie so weit sind.</p></li><li><p>Geben Sie das Passwort des Benutzers auf dem Intranator Server ein.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector33.png"></div></div></li><li><p>Es startet die lokale Konvertierung der Daten. Sobald dies abgeschlossen
                        ist, &ouml;ffnet sich die Oberfl&auml;che des Intra2net Groupware Clients. Pr&uuml;fen Sie
                        hier die Konfiguration des Kontos auf dem Server.</p></li><li><p>Ist die Konfiguration korrekt, so k&ouml;nnen Sie die serverseitige
                        Konvertierung durch das Anklicken der Checkbox <span class="guilabel">Starte
                            serverseitige Konvertierung</span> ansto&szlig;en.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector35.png"></div></div></li><li><p>Nach dem Start der serverseitigen Konvertierung werden Sie aufgefordert,
                        Outlook neu zu starten.</p><p>Beenden Sie dazu Outlook. Warten Sie dann, bis sich Outlook vollst&auml;ndig
                        beendet hat. Dies kann bis zu einer Minute dauern. Kontrollieren Sie am
                        besten &uuml;ber den Task-Manager von Windows, dass kein Prozess namens
                            <code class="computeroutput">OUTLOOK.EXE</code> mehr l&auml;uft. Starten Sie
                        erst dann Outlook neu.</p><p>Beachten Sie diese Vorgehensweise bitte auch bei den folgenden
                        Schritten.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/taskmgr.png"></div></div></li><li><p>Nach einem weiteren Neustart &ouml;ffnet sich die Oberfl&auml;che des Intra2net
                        Groupware Clients mit dem Men&uuml; <span class="guimenu">Sync-Status</span>. Es wird jetzt
                        Ordner f&uuml;r Ordner auf den Server synchronisiert. Alle fertig konvertierten
                        Ordner werden hier aufgef&uuml;hrt.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector40.png"></div></div></li><li><p>Warten Sie bis alle Ordner konvertiert sind. Sie werden dann zum Neustart
                        von Outlook aufgefordert.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector41.png"></div></div></li><li><p>Nach einem weiteren Neustart von Outlook ist die Konvertierung
                        abgeschlossen. Alle Groupware-Ordner wurden mit dem Konto auf dem Server
                        verbunden, nicht aber die E-Mail-Ordner.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector42.png"></div></div></li><li><p>Beenden Sie Outlook, warten bis der Prozess wirklich beendet ist und
                        starten es neu.</p></li><li><p>Warten Sie bis Outlook vollst&auml;ndig gestartet ist und schlie&szlig;en es
                        wieder.</p></li><li><p>&Ouml;ffnen die Windows-Systemsteuerung, Men&uuml; <span class="guimenu">E-Mail (32
                            Bit)</span>. Lassen Sie sich die Profile anzeigen.</p></li><li><p>Das f&uuml;r die Migration verwendete Outlook-Profil wird nun nicht mehr
                        ben&ouml;tigt. L&ouml;schen Sie es daher.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector42a.png"></div></div></li><li><p>Legen Sie ein neues Profil an und konfigurieren es f&uuml;r den Groupware
                        Client. Die daf&uuml;r n&ouml;tigen Schritte werden in <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="groupware-client-installation-config-ol2010.php">Abschnitt&nbsp;19.4, &#8222;Grundkonfiguration mit Outlook 2010&#8220;</a>, bzw. f&uuml;r
                        andere Versionen von Outlook in den anderen Abschnitten des selben Kapitels,
                        erkl&auml;rt.</p></li><li><p>Konfigurieren Sie das Konto f&uuml;r den Groupware Client wie in <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="groupware-client-account.php#groupware-client-account-groupware">Abschnitt&nbsp;20.1, &#8222;Groupware-Konto&#8220;</a> erkl&auml;rt. Der Groupware
                        Client beginnt danach automatisch, die Ordner mit Groupware-Daten vom Server
                        zu synchronisieren.</p></li><li><p>Die Groupwareordner sind nun noch parallel im E-Mail-Konto abonniert und
                        k&ouml;nnen Verwirrung beim Benutzer stiften. Diese Abos werden daher in den
                        folgenden Schritten gek&uuml;ndigt.</p></li><li><p>Klicken Sie mit der rechten Maustaste auf den Posteingang des direkt von
                        Outlook verwalteten IMAP-Kontos in der Ordnerliste. Es &ouml;ffnet sich ein
                        Kontextmen&uuml;. W&auml;hlen Sie dort
                        <span class="guimenuitem">IMAP-Ordner...</span></p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/config-imap-subscription01.png"></div></div></li><li><p>Klicken Sie auf <span class="guibutton">Abfrage</span>, um eine Liste aller
                        verf&uuml;gbaren Ordner vom Server abzurufen.</p></li><li><p>Markieren Sie alle Groupware-Ordner (wie z.B. Kalender, Kontakte, Notizen,
                        etc.) und klicken auf <span class="guibutton">Abo k&uuml;ndigen</span>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector43.png"></div></div></li><li><p>&Ouml;ffnen Sie die Oberfl&auml;che des Intra2net Groupware Clients mit dem Men&uuml;
                            <span class="guimenu">Meine Freigaben</span>. Gehen Sie Ordner f&uuml;r Ordner durch
                        und kontrollieren, ob die Zugriffsrechte korrekt gesetzt sind. Korrigieren
                        Sie diese bei Bedarf. </p></li><li><p>Sie k&ouml;nnen nun die freigegebenen Ordner anderer Benutzer wieder verbinden.
                        Die daf&uuml;r n&ouml;tigen Schritte finden Sie in <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="groupware-client-access-subscribe.php">Abschnitt&nbsp;21.2, &#8222;Fremde Ordner verbinden&#8220;</a> erkl&auml;rt.</p></li></ol></div><p>Wird dasselbe Konto auf dem Server auf verschiedenen Rechnern mit Outlook
                verwendet, k&ouml;nnen Sie nun die anderen Rechner umstellen. Konvertieren Sie auf diesen
                Rechnern nicht das Konto erneut wie hier beschrieben, da dies zu Duplikaten f&uuml;hren
                kann. Richten Sie dort stattdessen ein neues Profil f&uuml;r den Intra2net Groupware
                Client ein und laden die Daten vom Server.</p><a class="indexterm" name="d0e8891"></a><a class="indexterm" name="d0e8892"></a><a class="indexterm" name="d0e8893"></a></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="groupware-client-migrate-connector.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="groupware-client-migrate-connector.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="groupware-client-migrate-connector-manual.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">24. Kapitel - Migration vom Intranator Groupware Connector&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;24.3. Die manuelle Migration</td></tr></table></div>
      
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