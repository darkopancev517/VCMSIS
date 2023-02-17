<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>IMAP E-Mail-Konto | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="groupware-client-account.php" title="20. Kapitel - Konten konfigurieren"><link rel="prev" href="groupware-client-account.php" title="20. Kapitel - Konten konfigurieren"><link rel="next" href="groupware-client-account-import.php" title="20.3. Bestehende Daten &uuml;bernehmen">
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

<a href="groupware-client-account-email.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="groupware-client-account-email.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">20.2. IMAP E-Mail-Konto</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="groupware-client-account.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">20. Kapitel - Konten konfigurieren</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="groupware-client-account-import.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="groupware-client-account-email"></a>20.2. IMAP E-Mail-Konto</h2></div></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="groupware-client-account-email-view"></a>20.2.1. Ansicht</h3></div></div></div><p>In der Ordnerliste von Outlook auf der linken Seite werden diese beiden Konten
                angezeigt. Das E-Mail-Konto ist dabei standardm&auml;&szlig;ig mit der E-Mail-Adresse
                benannt.</p><p>Neu eingehende E-Mails erscheinen im Ordner Posteingang dieses Kontos.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/config-imap01.png"></div></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="groupware-client-account-email-subscription"></a>20.2.2. Abonnieren von Ordnern</h3></div></div></div><a class="indexterm" name="groupware-client-account-email-subscription1"></a><a class="indexterm" name="groupware-client-account-email-subscription2"></a><a class="indexterm" name="groupware-client-account-email-subscription3"></a><p>Outlook zeigt nicht alle in dem Konto verf&uuml;gbaren Ordner an, sondern nur die
                abonnierten. Wollen Sie weitere Ordner nutzen, m&uuml;ssen Sie diese zuerst abonnieren.
                Gehen Sie dazu wie folgt vor:</p><div class="procedure"><ol type="1"><li><p>Klicken Sie mit der rechten Maustaste auf den Posteingang in der
                        Ordnerliste. Es &ouml;ffnet sich ein Kontextmen&uuml;. W&auml;hlen Sie dort
                            <span class="guimenuitem">IMAP-Ordner...</span></p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/config-imap-subscription01.png"></div></div></li><li><p>Klicken Sie auf <span class="guibutton">Abfrage</span> um eine Liste aller
                        verf&uuml;gbaren Ordner vom Server abzurufen.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/config-imap-subscription02.png"></div></div></li><li><p>Es werden alle verf&uuml;gbaren eigenen Ordner, sowie die von anderen Benutzern
                        f&uuml;r Sie freigegebenen Ordner, angezeigt. Es werden sowohl Ordner mit
                        E-Mails, als auch Ordner mit Groupware-Objekten angezeigt. Achten Sie
                        darauf, in dieser Maske nur Ordner zu abonnieren, die tats&auml;chlich E-Mails
                        enthalten.</p><p>Markieren Sie alle gew&uuml;nschten Ordner und klicken auf
                            <span class="guibutton">Abonnieren</span>.</p></li></ol></div><p>Um Ordner mit Groupware-Inhalten zu abonnieren siehe <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="groupware-client-access-subscribe.php">Abschnitt&nbsp;21.2, &#8222;Fremde Ordner verbinden&#8220;</a>
                bzw. <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="groupware-client-extended-manual-map.php">Abschnitt&nbsp;22.2, &#8222;Ordner manuell verbinden&#8220;</a> (Eigene Ordner).</p><a class="indexterm" name="d0e6699"></a><a class="indexterm" name="d0e6700"></a><a class="indexterm" name="d0e6701"></a></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="groupware-client-account-email-sent"></a>20.2.3. Ordner f&uuml;r Gesendete Elemente</h3></div></div></div><a class="indexterm" name="groupware-client-account-email-sent1"></a><p>In der Standardkonfiguration werden gesendete E-Mails und Einladungen nicht auf
                dem Server, sondern nur lokal gespeichert. Sie k&ouml;nnen daher nicht von anderen
                Ger&auml;ten aus genutzt oder mit Kollegen geteilt werden. Au&szlig;erdem sind sie nicht im
                Backup enthalten.</p><p>Gehen Sie wie folgt vor, um die E-Mails auf dem Server zu speichern und diese
                Nachteile zu beheben:</p><div class="sect3" lang="de"><div class="titlepage"><div><div><h4 class="title"><a name="groupware-client-account-email-sent-ol2013"></a>20.2.3.1. Outlook 2013</h4></div></div></div><p>In Outlook 2013 k&ouml;nnen die Ordner f&uuml;r gesendete E-Mails, gel&ouml;schte E-Mails und
                    Entw&uuml;rfe nicht manuell eingestellt werden, sondern m&uuml;ssen vom IMAP-Server
                    &uuml;bermittelt werden (XLIST-Erweiterung). Die &uuml;bermittelten Ordnernamen werden
                    aber nur beim ersten Einrichten des Kontos in Outlook ausgelesen, sp&auml;tere
                    &Auml;nderungen auf dem Server werden von Outlook nicht nachvollzogen. Daher m&uuml;ssen
                    die Ordner bereits vor dem Einrichten von Outlook auf dem Server richtig
                    konfiguriert sein.</p><p>Auf dem Intranator Server k&ouml;nnen die per XLIST &uuml;bermittelten Ordner im Men&uuml;
                    Benutzermanager&nbsp;&gt;&nbsp;Benutzer&nbsp;:&nbsp;Groupware konfiguriert
                    werden.</p><p>Sollen &Auml;nderungen auf dem Server in einem bereits bestehenden Outlook-Konto
                    wirksam werden, so entfernen Sie das Konto &uuml;ber die Outlook-Kontensteuerung und
                    f&uuml;gen es danach neu hinzu. Sie m&uuml;ssen dabei nur das Outlook-IMAP-Konto
                    entfernen, die Datendatei des Groupware Clients oder weitere Konten k&ouml;nnen
                    bestehen bleiben.</p></div><div class="sect3" lang="de"><div class="titlepage"><div><div><h4 class="title"><a name="groupware-client-account-email-sent-ol2010"></a>20.2.3.2. Outlook 2010 und Outlook 2007</h4></div></div></div><div class="procedure"><ol type="1"><li><p>&Ouml;ffnen Sie das Men&uuml;
                                <span class="guimenu">Datei&nbsp;&gt;&nbsp;Kontoeinstellungen</span>, bzw.
                                <span class="guimenu">Extras&nbsp;&gt;&nbsp;Kontoeinstellungen</span> in
                            Outlook 2007. W&auml;hlen Sie das IMAP-Konto aus und klicken auf
                                <span class="guibutton">&Auml;ndern</span>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/config-imap-sent01.png"></div></div></li><li><p>&Ouml;ffnen Sie <span class="guibutton">Weitere Einstellungen</span>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/config-imap-sent02.png"></div></div></li><li><p>Wechseln Sie auf den Reiter <span class="guimenu">Gesendete
                            Elemente</span>.</p></li><li><p>Lassen Sie die gesendeten Elemente in einem Ordner auf dem Server
                            speichern und markieren den Ordner <code class="computeroutput">Gesendete
                                Elemente</code> unterhalb des Posteingangs.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/config-imap-sent03.png"></div></div></li><li><p>Best&auml;tigen Sie die &Auml;nderungen mit <span class="guibutton">OK</span> und
                            schlie&szlig;en den Assistenten zur Konto&auml;nderung ab. Alle gesendeten E-Mails
                            und Einladungen werden von nun an auf dem Server abgelegt.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/config-imap-sent05.png"></div></div></li></ol></div></div><div class="sect3" lang="de"><div class="titlepage"><div><div><h4 class="title"><a name="groupware-client-account-email-sent-ol2003"></a>20.2.3.3. Outlook 2003</h4></div></div></div><p>Die in Outlook 2003 integrierte IMAP-Funktionalit&auml;t erm&ouml;glicht nicht, die
                    gesendeten E-Mails auf dem Server abzulegen. Diese Funktion &uuml;bernimmt daher der
                    Intra2net Groupware Client.</p><p>Gehen Sie wie folgt vor um dies zu konfigurieren:</p><div class="procedure"><ol type="1"><li><p>&Ouml;ffnen Sie das Men&uuml; <span class="guimenu">Groupware Client&nbsp;&gt;&nbsp;Ordner
                                verbinden</span>.</p></li><li><p>Klicken Sie mit der rechten Maustaste auf den Ordner
                                <code class="computeroutput">Gesendete Objekte</code>. Es &ouml;ffnet sich
                            das Kontextmen&uuml;.</p></li><li><p>Deaktivieren Sie die Option <span class="guimenuitem">Ordnerstruktur nicht
                                synchronisieren</span>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/config-unskip-sent.png"></div></div></li></ol></div><a class="indexterm" name="d0e6809"></a></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="groupware-client-account-email-deleted"></a>20.2.4. Behandlung von gel&ouml;schten E-Mails</h3></div></div></div><a class="indexterm" name="groupware-client-account-email-deleted1"></a><a class="indexterm" name="groupware-client-account-email-deleted2"></a><p>Das IMAP-Protokoll sieht beim L&ouml;schen von E-Mails vor, dass sie mit einer
                speziellen L&ouml;schmarkierung in ihrem bisherigen Ordner verbleiben. Die so markierten
                E-Mails werden dann mit einem speziellen Befehl endg&uuml;ltig gel&ouml;scht.</p><p>Dies unterscheidet sich von der in Outlook &uuml;blichen Vorgehensweise, die gel&ouml;schten
                Elemente in einen speziellen Ordner zu verschieben und sie dort nach einiger Zeit
                endg&uuml;ltig zu l&ouml;schen.</p><p>Im Folgenden wird beschrieben, wie die einzelnen Outlook-Versionen mit diesem
                Unterschied umgehen und was es f&uuml;r Anpassungsm&ouml;glichkeiten f&uuml;r die Benutzer
                gibt.</p><div class="sect3" lang="de"><div class="titlepage"><div><div><h4 class="title"><a name="groupware-client-account-email-deleted-ol2013"></a>20.2.4.1. Outlook 2013</h4></div></div></div><p>In Outlook 2013 werden gel&ouml;schte E-Mails auf dem Server sofort gel&ouml;scht und in
                    Outlook lokal im Ordner "Gel&ouml;schte Elemente (Nur dieser Computer)"
                    abgelegt.</p><p>Abh&auml;ngig von der Einstellung <span class="guimenuitem">Beim Beenden von Outlook die Ordner
                        "Gel&ouml;schte Elemente" leeren</span> im Men&uuml;
                        <span class="guimenu">Datei&nbsp;&gt;&nbsp;Optionen&nbsp;&gt;&nbsp;Erweitert</span>
                    wird dieser Ordner endg&uuml;ltig aufger&auml;umt.</p></div><div class="sect3" lang="de"><div class="titlepage"><div><div><h4 class="title"><a name="groupware-client-account-email-deleted-ol2010"></a>20.2.4.2. Outlook 2010</h4></div></div></div><div class="procedure"><ol type="1"><li><p>&Ouml;ffnen Sie das Men&uuml;
                                <span class="guimenu">Datei&nbsp;&gt;&nbsp;Kontoeinstellungen</span>. W&auml;hlen
                            Sie das IMAP-Konto aus und klicken auf
                            <span class="guibutton">&Auml;ndern</span>.</p></li><li><p>&Ouml;ffnen Sie <span class="guibutton">Weitere Einstellungen</span> und den Reiter
                                <span class="guilabel">Gel&ouml;schte Elemente</span>.</p></li><li><p>Sie haben jetzt die M&ouml;glichkeit, die gel&ouml;schten E-Mails beim Verlassen
                            eines Ordners endg&uuml;ltig l&ouml;schen zu lassen, oder die E-Mails beim L&ouml;schen
                            in einen speziellen Order zu verschieben.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/imap-delmail-ol2010.png"></div></div></li></ol></div></div><div class="sect3" lang="de"><div class="titlepage"><div><div><h4 class="title"><a name="groupware-client-account-email-deleted-ol2007"></a>20.2.4.3. Outlook 2007</h4></div></div></div><div class="procedure"><ol type="1"><li><p>&Ouml;ffnen Sie das Men&uuml;
                                <span class="guimenu">Extras&nbsp;&gt;&nbsp;Kontoeinstellungen</span>. W&auml;hlen
                            Sie das IMAP-Konto aus und klicken auf
                            <span class="guibutton">&Auml;ndern</span>.</p></li><li><p>&Ouml;ffnen Sie <span class="guibutton">Weitere Einstellungen</span> und den Reiter
                                <span class="guilabel">Allgemein</span>.</p></li><li><p>Sie haben jetzt die M&ouml;glichkeit, die gel&ouml;schten E-Mails automatisch
                            beim Verlassen eines Ordners endg&uuml;ltig l&ouml;schen zu lassen.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/imap-delmail-ol2007.png"></div></div></li></ol></div></div><div class="sect3" lang="de"><div class="titlepage"><div><div><h4 class="title"><a name="groupware-client-account-email-deleted-ol2003"></a>20.2.4.4. Outlook 2003</h4></div></div></div><p>Gel&ouml;schte E-Mails werden nach dem L&ouml;schen durchgestrichen dargestellt.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/imap-delmail-ol2003-marked.png"></div></div><p>Um Sie endg&uuml;ltig zu L&ouml;schen verwenden Sie das Men&uuml;
                        <span class="guimenu">Bearbeiten&nbsp;&gt;&nbsp;Gel&ouml;schte Nachrichten permanent
                        l&ouml;schen</span>. Das endg&uuml;ltige L&ouml;schen ist nur f&uuml;r den aktuell ge&ouml;ffneten
                    Ordner wirksam.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/imap-delmail-ol2003-del.png"></div></div><a class="indexterm" name="d0e6916"></a><a class="indexterm" name="d0e6917"></a></div></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="groupware-client-account.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="groupware-client-account.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="groupware-client-account-import.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">20. Kapitel - Konten konfigurieren&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;20.3. Bestehende Daten &uuml;bernehmen</td></tr></table></div>
      
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