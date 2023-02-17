<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Grundkonfiguration mit Outlook 2013 | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="groupware-client-installation.php" title="19. Kapitel - Installation"><link rel="prev" href="groupware-client-installation-activedirectory.php" title="19.2. Verteilung des Programms &uuml;ber Active Directory"><link rel="next" href="groupware-client-installation-config-ol2010.php" title="19.4. Grundkonfiguration mit Outlook 2010">
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

<a href="groupware-client-installation-config-ol2013.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="groupware-client-installation-config-ol2013.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">19.3. Grundkonfiguration mit Outlook 2013</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="groupware-client-installation-activedirectory.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">19. Kapitel - Installation</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="groupware-client-installation-config-ol2010.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="groupware-client-installation-config-ol2013"></a>19.3. Grundkonfiguration mit Outlook 2013</h2></div></div></div><a class="indexterm" name="groupware-client-installation-config-ol2013-1"></a><a class="indexterm" name="groupware-client-installation-config-ol2013-2"></a><p>Outlook verwendet den Intra2net Groupware Client, indem ein spezieller Typ von
            Datendatei in ein Outlook-Profil eingebunden wird. Legen Sie wie im Folgenden
            beschrieben ein neues, leeres Profil an, konfigurieren ein E-Mail-Konto und binden die
            spezielle Datendatei ein.</p><p>Legen Sie unbedingt immer ein neues Profil an, auch wenn Sie Daten aus einer
            bestehenden Outlook-Konfiguration &uuml;bernehmen wollen. Bestehende Daten k&ouml;nnen nach der
            Grundkonfiguration in das neue Profil importiert werden. Dies wird in <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="groupware-client-account-import.php">Abschnitt&nbsp;20.3, &#8222;Bestehende Daten &uuml;bernehmen&#8220;</a>
            beschrieben.</p><div class="procedure"><ol type="1"><li><p>&Ouml;ffnen Sie die Windows-Systemsteuerung, Men&uuml;punkt <span class="guimenuitem">E-Mail
                        (32-Bit)</span>.</p></li><li><p>&Ouml;ffnen Sie den Profil-Editor</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/install-ol2013-profile01.png"></div></div></li><li><p>F&uuml;gen Sie ein neues Profil hinzu und vergeben einen Namen</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/install-ol2013-profile02.png"></div></div><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/install-ol2013-profile03.png"></div></div></li><li><a class="indexterm" name="groupware-client-installation-config-ol2013-3"></a><p>W&auml;hlen Sie manuelle Konfiguration mit POP oder IMAP.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/install-ol2013-profile04.png"></div></div><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/install-ol2013-profile05.png"></div></div></li><li><p>Stellen Sie den Kontotyp auf IMAP und tragen die Benutzer- und Serverdaten
                    ein.</p><p>Verwenden Sie als Postein- und -ausgangsserver Ihren Intranator Server.
                    Verwenden Sie unbedingt den vollst&auml;ndigen DNS-Namen inkl. Domain Ihres
                    Intranator Servers, tragen Sie keine IP-Adressen ein.</p><p>Soll der Client auch von au&szlig;erhalb des lokalen Netzes zugreifen k&ouml;nnen, so
                    verwenden Sie den externen DNS-Namen des Intranator Servers. Verwenden Sie auch
                    hier keine IP-Adresse, sondern registrieren gegebenenfalls f&uuml;r Ihren Intranator
                    Server einen DNS-Namen bei Ihrem Domainprovider oder DynDNS-Anbieter.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/install-ol2013-profile-imap01.png"></div></div></li><li><p>&Ouml;ffnen Sie die <span class="guibutton">Weiteren Einstellungen</span> und den Reiter
                        <span class="guimenu">Postausgangsserver</span>. Aktivieren Sie die
                    SMTP-Authentifizierung mit den gleichen Einstellungen wie f&uuml;r den
                    Posteingangsserver.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/install-ol2013-profile-imap02.png"></div></div></li><li><p>&Ouml;ffnen Sie den Reiter <span class="guimenu">Erweitert</span>. Stellen Sie die
                    Verschl&uuml;sselung f&uuml;r IMAP auf <span class="guimenuitem">SSL</span> und die f&uuml;r SMTP auf
                        <span class="guimenuitem">TLS</span>. &Auml;ndern Sie die Portnummer f&uuml;r den
                    Postausgangsserver auf <strong class="userinput"><code>587</code></strong> (f&uuml;r SMTP Submission / MSA).
                    Schlie&szlig;en Sie die E-Mail-Einstellungen.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/install-ol2013-profile-imap03.png"></div></div></li><li><p>Testen Sie die Kontoeinstellungen durch einen Klick auf
                        <span class="guibutton">Weiter</span>.</p><div class="orderedlist"><ol type="a"><li><p>Geht der Test erfolgreich durch, k&ouml;nnen Sie die n&auml;chsten Schritte zur
                            Zertifikatsinstallation &uuml;berspringen.</p></li><li><p>Wird Ihnen die Fehlermeldung <code class="computeroutput">Der Zielprinzipalname ist
                                falsch</code> oder eine Fehlermeldung zum
                            G&uuml;ltigkeitszeitraum des Zertifikats angezeigt, m&uuml;ssen Sie zuerst auf dem
                            Intranator Server ein passendes Zertifikat anlegen und/oder die
                            DNS-Einstellungen anpassen. Weitere Informationen finden Sie im <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="base-ssl-encryption.php">10. Kapitel,&nbsp;&#8222;SSL-Verschl&uuml;sselung und Zertifikate&#8220;</a>.</p></li><li><p>Wird Ihnen eine Internetsicherheitswarnung wegen eines nicht
                            vertrauensw&uuml;rdigen Stammzertifikats angezeigt, gehen Sie auf
                                <span class="guibutton">Zertifikat anzeigen...</span>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/install-ol2013-profile-imap04.png"></div></div></li></ol></div></li><li><p>Gehen Sie auf <span class="guibutton">Zertifikat installieren...</span>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/install-ol2013-profile-imap05.png"></div></div></li><li><p>Es &ouml;ffnet sich der Assistent zur Zertifikatsinstallation. Lassen Sie das
                    Zertifikat in einem speziellen Speicher ablegen und klicken auf
                        <span class="guibutton">Durchsuchen</span>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/install-ol2013-profile-imap06.png"></div></div></li><li><p>W&auml;hlen Sie den Zertifikatsspeicher <span class="guilabel">Vertrauensw&uuml;rdige
                        Stammzertifizierungsstellen</span> aus.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/install-ol2013-profile-imap07.png"></div></div></li><li><p>Best&auml;tigen Sie die Installation des Zertifikats.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/install-ol2013-profile-imap08.png"></div></div></li><li><p>Brechen Sie die Sicherheitswarnung mit <span class="guibutton">Nein</span> ab und
                    schlie&szlig;en das Testfenster.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/install-ol2013-profile-imap09.png"></div></div></li><li><a name="groupware-client-installation-config-ol2013-imap-test-success"></a><p>Starten Sie erneut einen Test der Kontoeinstellungen. Diesmal muss die
                    Verbindung ohne Sicherheitswarnung erfolgreich durchlaufen.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/install-ol2013-profile-imap10.png"></div></div></li><li><p>Beenden Sie die Kontokonfiguration.</p><div class="caution" style="margin-left: 0.2in; margin-right: 0.5in;"><table border="0" summary="Caution"><tr><td rowspan="2" align="center" valign="top" width="25"><img alt="[Achtung]" src="../images/admon/caution.png"></td><th align="left">Achtung</th></tr><tr><td align="left" valign="top"><p>Starten Sie in diesem Zustand auf keinen Fall Outlook. Gehen Sie zuerst
                        die folgenden Schritte dieser Anleitung durch. Ein Start von Outlook in
                        diesem Moment w&uuml;rde alle Groupware-Standardordner in der falschen Datendatei
                        anlegen und damit das Profil unbrauchbar machen.</p></td></tr></table></div></li><li><p>&Ouml;ffnen Sie die Eigenschaften des neuen Profils. W&auml;hlen Sie Bearbeiten der
                    Datendateien.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/install-ol2013-profile-pst01.png"></div></div><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/install-ol2013-profile-pst02.png"></div></div></li><li><p>F&uuml;gen Sie eine neue Datendatei vom Typ <span class="guimenuitem">Intranator Groupware
                        Client Datendatei (.mxstore)</span> hinzu.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/install-ol2013-profile-pst03.png"></div></div><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/install-ol2013-profile-pst04.png"></div></div></li><li><p>W&auml;hlen Sie einen Ordner in dem die Datendatei des Intra2net Groupware Clients
                    gespeichert werden soll.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/install-ol2013-profile-pst05.png"></div></div></li><li><p>Die neue Datendatei wurde hinzugef&uuml;gt. Nehmen Sie <span class="emphasis"><em>keine</em></span>
                    Ver&auml;nderung an der Festlegung der Standarddatendatei vor, dies geschieht sp&auml;ter
                    automatisch.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/install-ol2013-profile-pst06.png"></div></div></li><li><p>Schlie&szlig;en Sie den Dialog.</p></li><li><p>Wenn Sie m&ouml;chten, k&ouml;nnen Sie Outlook automatisch beim Start das eben erstellte
                    Profil &ouml;ffnen lassen.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/install-ol2013-profile-pst07.png"></div></div></li><li><p>Starten Sie Outlook mit dem eben neu erstellten Profil. Es &ouml;ffnet sich
                    automatisch der Dialog <span class="guimenu">Server-Konten</span> des Intra2net Groupware
                    Clients.</p></li><li><p>Fahren Sie mit der Einrichtung im <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="groupware-client-account.php">20. Kapitel,&nbsp;&#8222;Konten konfigurieren&#8220;</a> fort. Kehren Sie bei
                    Synchronisationsproblemen mit den E-Mails zu <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="groupware-client-installation-config-ol2013.php#groupware-client-installation-config-ol2013-imap-problems">Abschnitt&nbsp;19.3.1, &#8222;Beheben von falsch erkannten Ordnerhierarchien&#8220;</a>zur&uuml;ck.</p></li></ol></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="groupware-client-installation-config-ol2013-imap-problems"></a>19.3.1. Beheben von falsch erkannten Ordnerhierarchien</h3></div></div></div><p>Microsoft hat f&uuml;r Outlook 2013 die Unterst&uuml;tzung des IMAP-Protokolls vollst&auml;ndig
                neu entwickelt. Diese neuen Programmteile k&ouml;nnen in einigen Konstellationen aber
                noch Probleme machen. Im Folgenden wird erkl&auml;rt wie man diese behebt.</p><p>Die Probleme &auml;u&szlig;ern sich meist dadurch, da&szlig; bei einigen oder allen E-Mail-Ordnern
                Synchronisationsprobleme auftreten. Dies bedeutet, da&szlig; E-Mails vom Server nicht
                angezeigt und lokale &Auml;nderungen nicht auf den Server geschrieben werden.
                Gleichzeitig erscheinen Fehlermeldungen im Ordner
                    <code class="computeroutput">Synchronisierungsprobleme (Nur dieser
                Computer)</code>. In vielen F&auml;llen wird der Posteingang selbst korrekt
                synchronisiert, die Unterordner darunter aber nicht.</p><p>In anderen F&auml;llen kommt es vor, dass Outlook die auf dem Server liegenden Ordner
                an einer falschen Stelle in der Hierarchie oder doppelt anzeigt.</p><p>Ursache hinter diesen Problemen ist, dass Outlook die auf dem Server vorliegende
                Ordnerhierarchie falsch der lokalen Ordnerhierarchie zuordnet. Mit folgenden
                Schritten bringen Sie Outlook dazu, die Ordnerhierarchie korrekt zuzuordnen:</p><div class="procedure"><ol type="1"><li><p>&Ouml;ffnen Sie die Windows-Systemsteuerung, Men&uuml;punkt <span class="guimenuitem">E-Mail
                            (32-Bit)</span>.</p></li><li><p>&Ouml;ffnen Sie den Profil-Editor</p></li><li><p>W&auml;hlen Sie das mit dem Intra2net Groupware Client verwendete Profil und
                        &ouml;ffnen dessen Eigenschaften.</p></li><li><p>W&auml;hlen Sie <span class="guibutton">E-Mail-Konten...</span>, markieren das
                        IMAP-Konto und <span class="guibutton">&Auml;ndern...</span>.</p></li><li><p>&Ouml;ffnen Sie die <span class="guibutton">Weitere Einstellungen</span> und darin den
                        Reiter <span class="guimenu">Erweitert</span>.</p></li><li><p>Tragen Sie im <span class="guimenuitem">Stammordnerpfad</span> den Text
                            <strong class="userinput"><code>INBOX</code></strong> ein und speichern mit
                            <span class="guibutton">OK</span>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/install-ol2013-problem-inbox.png"></div></div></li><li><p>Schlie&szlig;en Sie die Systemsteuerung und starten Outlook</p></li><li><p>Klicken Sie mir Rechts auf das Wurzelverzeichnis der E-Mail-Datendatei und
                        w&auml;hlen die Funktion <span class="guimenuitem">Ordnerliste
                        aktualisieren</span>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/install-ol2013-problem-update.png"></div></div></li><li><p>Warten Sie kurz bis Outlook die Ordnerliste aktualisiert hat. Es ist nicht
                        ungew&ouml;hnlich, wenn in diesem Zustand einige Ordner doppelt angezeigt
                        werden.</p></li><li><p>Schlie&szlig;en Sie Outlook.</p></li><li><p>&Ouml;ffnen Sie wieder die Systemsteuerung und gehen zum
                            <span class="guimenu">Erweitert</span>-Reiter des IMAP-Kontos (siehe oben).</p></li><li><p>L&ouml;schen Sie die Einstellung bei <span class="guimenuitem">Stammordnerpfad</span>
                        wieder.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/install-ol2013-problem-no-inbox.png"></div></div></li><li><p>Speichern Sie und &ouml;ffnen Outlook.</p></li><li><p>Klicken Sie mir Rechts auf das Wurzelverzeichnis der E-Mail-Datendatei und
                        w&auml;hlen die Funktion <span class="guimenuitem">Ordnerliste
                        aktualisieren</span>.</p></li><li><p>Jetzt sollte die Ordnerhierarchie korrekt dargestellt werden. In einigen
                        F&auml;llen kann es n&ouml;tig sein, mehrfach die Ordnerliste zu aktualisieren.</p></li><li><p>Vergleichen Sie den Inhalt der Ordner mit der Webgroupware und pr&uuml;fen
                        damit, ob jetzt alle Ordner korrekt synchronisiert werden.</p></li></ol></div><a class="indexterm" name="d0e5947"></a><a class="indexterm" name="d0e5948"></a><a class="indexterm" name="d0e5949"></a></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="groupware-client-installation-activedirectory.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="groupware-client-installation.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="groupware-client-installation-config-ol2010.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">19.2. Verteilung des Programms &uuml;ber Active Directory&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;19.4. Grundkonfiguration mit Outlook 2010</td></tr></table></div>
      
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