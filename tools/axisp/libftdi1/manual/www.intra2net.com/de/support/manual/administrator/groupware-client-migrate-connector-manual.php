<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Die manuelle Migration | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="groupware-client-migrate-connector.php" title="24. Kapitel - Migration vom Intranator Groupware Connector"><link rel="prev" href="groupware-client-migrate-connector-automatic.php" title="24.2. Die automatische Migration"><link rel="next" href="groupware-client-reference.php" title="25. Kapitel - Referenzinformationen">
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

<a href="groupware-client-migrate-connector-manual.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="groupware-client-migrate-connector-manual.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">24.3. Die manuelle Migration</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="groupware-client-migrate-connector-automatic.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">24. Kapitel - Migration vom Intranator Groupware Connector</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="groupware-client-reference.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="groupware-client-migrate-connector-manual"></a>24.3. Die manuelle Migration</h2></div></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="groupware-client-migrate-connector-manual-overview"></a>24.3.1. &Uuml;berblick</h3></div></div></div><p>Hier ein grober &Uuml;berblick dar&uuml;ber, wie die manuelle Migration vor sich geht. Die
                einzelnen Schritte werden im folgenden Abschnitt ausf&uuml;hrlich erkl&auml;rt.</p><div class="itemizedlist"><ul type="disc"><li><p>Mit Hilfe des alten Groupware Connector die bestehenden Daten vollst&auml;ndig
                        mit dem Server synchronisieren.</p></li><li><p>Ein Backup der Daten auf Client und Server erstellen.</p></li><li><p>Den alten Groupware Connector deinstallieren, den neuen Intra2net
                        Groupware Client installieren.</p></li><li><p>Ein Profil f&uuml;r den neuen Groupware Client einrichten.</p></li><li><p>L&ouml;schen aller Ordner mit Aufgaben-, Kontakt- und Kalenderdaten &uuml;ber das
                        direkt von Outlook verwaltete IMAP-Konto.</p></li><li><p>Die Datendatei des alten Groupware Connectors in Outlook zus&auml;tzlich
                        &ouml;ffnen.</p></li><li><p>Die Ordner mit Aufgaben-, Kontakt- und Kalenderdaten per Drag &amp;
                        Drop in die Datendatei des Groupware Clients verschieben.</p></li><li><p>Abonnements von Groupwareordnern im direkt von Outlook verwalteten
                        IMAP-Konto aufr&auml;umen; Kontrolle der Freigaben an andere Benutzer.</p></li></ul></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="groupware-client-migrate-connector-manual-steps"></a>24.3.2. Die Migration in einzelnen Schritten</h3></div></div></div><div class="procedure"><ol type="1"><li><p>&Ouml;ffnen Sie Outlook mit dem Profil des Groupware Connectors. &Ouml;ffnen Sie die
                        KQueue im Infobereich der Tastleiste und lassen sich den Zustand der
                        Warteschlange anzeigen. Die Warteschlange muss leer sein (Anzeige:
                            <code class="computeroutput">0/0</code>), bevor Sie fortfahren
                        k&ouml;nnen.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/convert-connector01.png"></div></div></li><li><p>Schlie&szlig;en Sie Outlook.</p></li><li><p>Erstellen Sie eine Sicherheitskopie der Outlook-Datendatei des bisherigen
                        Groupware-Connector-Profils. Standardm&auml;&szlig;ig ist diese im Verzeichnis des
                        Benutzers unter <code class="filename">AppData\Roaming\Intra2net</code>, bzw.
                            <code class="filename">Lokale Einstellungen\Anwendungsdaten\Intra2net</code>, zu
                        finden.</p></li><li><p>Kontrollieren Sie, dass Sie &uuml;ber ein aktuelles Backup der Daten auf dem
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
                        nicht getan haben.</p></li><li><p>Legen Sie ein neues Outlook-Profil an und konfigurieren es f&uuml;r den
                        Groupware Client. Die daf&uuml;r n&ouml;tigen Schritte werden in <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="groupware-client-installation-config-ol2010.php">Abschnitt&nbsp;19.4, &#8222;Grundkonfiguration mit Outlook 2010&#8220;</a>, bzw. f&uuml;r
                        andere Versionen von Outlook in den anderen Abschnitten des selben Kapitels,
                        erkl&auml;rt.</p></li><li><p>Konfigurieren Sie das Konto f&uuml;r den Groupware Client wie in <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="groupware-client-account.php#groupware-client-account-groupware">Abschnitt&nbsp;20.1, &#8222;Groupware-Konto&#8220;</a> erkl&auml;rt. Der Groupware
                        Client beginnt danach automatisch die Ordner mit Groupware-Daten vom Server
                        zu synchronisieren.</p></li><li><p>Machen Sie alle Ordnertypen sichtbar, indem Sie auf die Ordnerliste
                        umschalten.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/import-folderlist.png"></div></div></li><li><p>&Ouml;ffnen Sie den Ordner <code class="computeroutput">Aufgaben</code>.
                        Allerdings nicht den normalen Aufgaben-Ordner unterhalb von
                            <span class="guimenuitem">Groupware Ordner</span>, sondern den Aufgaben-Ordner
                        unterhalb von Posteingang im direkt von Outlook verwalteten
                        IMAP-Konto (normalerweise mit der E-Mail-Adresse benannt).</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/manual-migrate-email1.png"></div></div></li><li><p>Kontrollieren Sie, dass keine normalen Aufgaben angezeigt werden, sondern
                        nur E-Mails mit langen, unverst&auml;ndlichen Zeichenketten als Betreff.
                        Ansonsten haben Sie den falschen Ordner ge&ouml;ffnet.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/manual-migrate-email2.png"></div></div></li><li><p>Markieren Sie alle E-Mails und l&ouml;schen diese. Verwenden Sie zum L&ouml;schen <span class="keycap"><strong>Shift</strong></span>+<span class="keycap"><strong>Entf</strong></span>, um den L&ouml;schvorgang zu beschleunigen. Best&auml;tigen Sie, dass Sie
                        die E-Mails endg&uuml;ltig l&ouml;schen wollen. L&ouml;schen Sie nur den Inhalt des
                        Ordners, lassen aber den Ordner selbst bestehen. </p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/manual-migrate-email3.png"></div></div></li><li><p>Werden alle E-Mails nun durchgestrichen dargestellt, wurden sie bisher nur
                        zum L&ouml;schen markiert. &Uuml;ber das Men&uuml;
                            <span class="guimenu">Bearbeiten&nbsp;&gt;&nbsp;Gel&ouml;schte Nachrichten
                            permanent l&ouml;schen</span> k&ouml;nnen Sie auf dem Server endg&uuml;ltig gel&ouml;scht
                        werden. Dieser Schritt betrifft prim&auml;r Outlook 2003.</p></li><li><p>&Ouml;ffnen Sie nun den normalen
                        <code class="computeroutput">Aufgaben</code>-Ordner unterhalb von
                            <span class="guimenuitem">Groupware Ordner</span>. Warten Sie, bis keinerlei
                        Eintr&auml;ge mehr angezeigt werden.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/manual-migrate-checkempty.png"></div></div></li><li><p>Wiederholen Sie die vorigen 5 Schritte f&uuml;r alle Ordner mit Aufgaben-,
                        Kalender- und Kontaktdaten.</p></li><li><p>&Ouml;ffnen Sie in Outlook das Men&uuml;
                            <span class="guimenu">Datei&nbsp;&gt;&nbsp;&Ouml;ffnen&nbsp;&gt;&nbsp;Outlook-Datendatei
                            &ouml;ffnen</span> (ab Outlook 2010), bzw.
                            <span class="guimenu">Datei&nbsp;&gt;&nbsp;&Ouml;ffnen&nbsp;&gt;&nbsp;Outlook-Datendatei</span>
                        (fr&uuml;here Versionen).</p></li><li><p>W&auml;hlen Sie die Datendatei des alten Groupware Connectors aus.</p></li><li><p>&Ouml;ffnen Sie den <code class="computeroutput">Aufgaben</code>-Ordner in der
                        eben ge&ouml;ffneten Datendatei.</p></li><li><p>Markieren Sie alle Elemente und verschieben sie per Drag &amp; Drop in
                        den <code class="computeroutput">Aufgaben</code>-Ordner des Groupware Clients
                        (unterhalb von <span class="guilabel">Groupware Ordner</span>).</p><div class="informaltable"><table border="0"><colgroup><col><col></colgroup><tbody><tr><td align="center">
                                        <div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/import-groupware-objects01.png"></div></div>
                                    </td><td align="center">
                                        <div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/import-groupware-objects02.png"></div></div>
                                    </td></tr></tbody></table></div></li><li><p>Wiederholen Sie dies f&uuml;r alle Ordner, die f&uuml;r Aufgaben, Kalender und
                        Kontakte verwendet werden. Um alle Kalendereintr&auml;ge markieren zu k&ouml;nnen,
                        verwenden Sie die Listenansicht (Men&uuml;
                            <span class="guimenu">Ansicht&nbsp;&gt;&nbsp;Ansicht
                            &auml;ndern&nbsp;&gt;&nbsp;Liste</span>).</p></li><li><p>Schlie&szlig;en Sie nun die Datendatei des alten Groupware Connectors. Klicken
                        Sie dazu mit der rechten Maustaste auf den Wurzelordner der Datendatei und
                        w&auml;hlen <span class="guimenuitem">Outlook-Datendatei schlie&szlig;en</span>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/import-close.png"></div></div></li><li><p>Die Groupwareordner sind nun noch parallel im E-Mail-Konto abonniert und
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
                        Die daf&uuml;r n&ouml;tigen Schritte finden Sie in <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="groupware-client-access-subscribe.php">Abschnitt&nbsp;21.2, &#8222;Fremde Ordner verbinden&#8220;</a> erkl&auml;rt.</p></li></ol></div></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="groupware-client-migrate-connector-automatic.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="groupware-client-migrate-connector.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="groupware-client-reference.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">24.2. Die automatische Migration&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;25. Kapitel - Referenzinformationen</td></tr></table></div>
      
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