<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Bestehende Daten &uuml;bernehmen | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="groupware-client-account.php" title="20. Kapitel - Konten konfigurieren"><link rel="prev" href="groupware-client-account-email.php" title="20.2. IMAP E-Mail-Konto"><link rel="next" href="groupware-client-access.php" title="21. Kapitel - Freigaben und Zugriff auf fremde Ordner">
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

<a href="groupware-client-account-import.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="groupware-client-account-import.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">20.3. Bestehende Daten &uuml;bernehmen</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="groupware-client-account-email.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">20. Kapitel - Konten konfigurieren</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="groupware-client-access.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="groupware-client-account-import"></a>20.3. Bestehende Daten &uuml;bernehmen</h2></div></div></div><a class="indexterm" name="groupware-client-account-existingdata1"></a><a class="indexterm" name="groupware-client-account-existingdata2"></a><a class="indexterm" name="groupware-client-account-existingdata3"></a><p>Verwenden Sie bisher Outlook mit einem anderen Profil und m&ouml;chten die dortigen Daten
            jetzt mit dem Intra2net Groupware Client nutzen, gehen Sie wie im Folgenden beschrieben
            vor.</p><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="groupware-client-account-import-prepare"></a>20.3.1. Vorbereiten der Datendatei</h3></div></div></div><p>Voraussetzung f&uuml;r die &Uuml;bernahme von Daten ist eine Outlook-Datendatei (.pst) die
                alle Daten enth&auml;lt. Outlook legt die Datendateien eines Profils in einem von der
                Outlook-Version abh&auml;ngigen Verzeichnis ab. Sie finden den Pfad zur
                Outlook-Datendatei wie im Folgenden beschrieben heraus:</p><div class="procedure"><ol type="1"><li><p>&Ouml;ffnen Sie die Windows-Systemsteuerung, Men&uuml;punkt <span class="guimenuitem">E-Mail
                            Setup (32-Bit)</span>.</p></li><li><p>&Ouml;ffnen Sie den Profil-Editor.</p></li><li><p>W&auml;hlen Sie das bisherige Profil und lassen Sie sich die Eigenschaften und
                        dort die Datendateien anzeigen.</p></li><li><p>Lassen Sie sich den Dateispeicherort der Datendatei anzeigen und notieren
                        sich den vollst&auml;ndigen Pfad dieser Datendatei.</p></li><li><p>Legen Sie mit einem Dateimanager eine Sicherheitskopie dieser Datendatei
                        an.</p></li></ol></div><p>Verwenden Sie zum &Uuml;bernehmen der Daten unbedingt eine lokale .pst-Datei. Versuchen
                Sie nicht das bisherige Groupwaresystem und den Groupware Client gleichzeitig in
                einem Profil einzusetzen, da dies zu St&ouml;rungen f&uuml;hren kann.</p></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="groupware-client-account-import-groupware"></a>20.3.2. &Uuml;bernehmen der Groupwaredaten</h3></div></div></div><p>Gehen Sie nun wie folgt vor um die Groupwaredaten durch Kopieren zu
                &uuml;bernehmen:</p><div class="procedure"><ol type="1"><li><p>Pr&uuml;fen Sie, dass Ihre eben erstellte Sicherheitskopie der
                        Outlook-Datendatei wirklich vollst&auml;ndig ist.</p></li><li><p>Starten Sie Outlook mit dem Profil des Groupware Clients.</p></li><li><p>&Ouml;ffnen Sie das Men&uuml;
                            <span class="guimenu">Datei&nbsp;&gt;&nbsp;&Ouml;ffnen&nbsp;&gt;&nbsp;Outlook-Datendatei
                            &ouml;ffnen</span> (ab Outlook 2010), bzw.
                            <span class="guimenu">Datei&nbsp;&gt;&nbsp;&Ouml;ffnen&nbsp;&gt;&nbsp;Outlook-Datendatei</span>
                        (fr&uuml;here Versionen).</p></li><li><p>W&auml;hlen Sie die Datendatei mit den zu &uuml;bernehmenden Daten aus.</p></li><li><p>Machen Sie alle Ordnertypen sichtbar in dem Sie auf die Ordnerliste
                        umschalten.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/import-folderlist.png"></div></div></li><li><p>&Ouml;ffnen Sie den ersten Standard-Groupwareordner (z.B. Aufgaben) in der eben
                        ge&ouml;ffneten Datendatei.</p></li><li><p>Markieren Sie alle Elemente und verschieben sie per Drag &amp; Drop in den
                        entsprechenden Ordner des Groupware Clients (unterhalb von
                            <span class="guilabel">Groupware Ordner</span>). Um alle Kalendereintr&auml;ge
                        markieren zu k&ouml;nnen, verwenden Sie die Listenansicht (Men&uuml;
                            <span class="guimenu">Ansicht&nbsp;&gt;&nbsp;Ansicht
                            &auml;ndern&nbsp;&gt;&nbsp;Liste</span>).</p><div class="informaltable"><table border="0"><colgroup><col><col></colgroup><tbody><tr><td align="center">
                                        <div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/import-groupware-objects01.png"></div></div>
                                    </td><td align="center">
                                        <div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/import-groupware-objects02.png"></div></div>
                                    </td></tr></tbody></table></div></li><li><p>Wiederholen Sie die letzten beiden Schritte f&uuml;r alle
                        Standard-Groupwareordner (Aufgaben, Kalender, Kontakte und Notizen).</p></li><li><p>Verschieben Sie alle nicht-Standard-Groupwareordner, nicht aber die
                        E-Mail-Ordner, Ordner f&uuml;r Ordner per Drag &amp; Drop in den Groupware Client
                        (unter <span class="guilabel">Groupware Ordner</span>).</p><div class="informaltable"><table border="0"><colgroup><col><col></colgroup><tbody><tr><td align="center">
                                        <div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/import-groupware-folder01.png"></div></div>
                                    </td><td align="center">
                                        <div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/import-groupware-folder02.png"></div></div>
                                    </td></tr></tbody></table></div><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/import-groupware-folder03.png"></div></div></li></ol></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="groupware-client-account-import-email"></a>20.3.3. &Uuml;bernehmen der E-Mails</h3></div></div></div><p>Pr&uuml;fen Sie zuerst, ob Sie die E-Mails aus der Outlook-Datendatei wirklich noch
                &uuml;bernehmen m&uuml;ssen, oder ob sie bereits auf dem Intranator Server liegen. Letzteres
                ist z.B. der Fall wenn der Intranator Server bisher bereits als reiner E-Mail-Server
                ohne Groupware verwendet wurde, oder wenn die E-Mails bereits per IMAP vom
                bisherigen E-Mail-Server kopiert wurden.</p><div class="informaltable"><table border="0"><colgroup><col align="left"><col align="right"></colgroup><tbody><tr><td align="left">
                                <p>F&uuml;r letzteres kann z.B. das Programm <a class="ulink" href="http://home.arcor.de/armin.diehl/imapcopy/imapcopy.html" target="_top">IMAPCopy</a> eingesetzt werden.</p>
                            </td><td align="right">
                                <div class="mediaobject"><img src="../images/groupware-client/qrcode-imapcopy.png"></div>
                            </td></tr></tbody></table></div><p>Liegen die E-Mails bereits auf dem Intranator Server, sollten Sie im von Outlook
                verwalteten IMAP-Konto (typischerweise mit der E-Mail-Adresse benannt) zu sehen
                sein. Es ist m&ouml;glich, dass Unterordner erst abonniert werden m&uuml;ssen bevor sie
                sichtbar werden. Die dazu n&ouml;tigen Schritte sind in <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="groupware-client-account-email.php#groupware-client-account-email-subscription">Abschnitt&nbsp;20.2.2, &#8222;Abonnieren von Ordnern&#8220;</a> beschrieben.</p><p>Ist ein &Uuml;bernehmen der E-Mails n&ouml;tig, gehen Sie daf&uuml;r wie folgt vor:</p><div class="procedure"><ol type="1"><li><p>&Ouml;ffnen Sie den Posteingang der zu importierenden Datendatei</p></li><li><p>Schauen Sie in der Statuszeile unten links nach der Anzahl der
                        E-Mails.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/import-email-count.png"></div></div><div class="orderedlist"><ol type="a"><li><p>Wenn es sich um weniger als 1000 Elemente handelt, k&ouml;nnen Sie alle
                                E-Mails markieren und per Drag &amp; Drop in den Posteingang des von
                                Outlook verwalteten IMAP-Kontos (typischerweise mit der
                                E-Mail-Adresse benannt) verschieben.</p></li><li><p>Wenn es sich um mehr als 1000 Elemente handelt, markieren Sie die
                                ersten ca. 1000 E-Mails. Sie k&ouml;nnen die markierte Anzahl anhand der
                                Gr&ouml;&szlig;e des Scrollbalkens rechts und der Gesamtanzahl absch&auml;tzen.
                                Verschieben Sie diese 1000 E-Mails dann per Drag &amp; Drop in den
                                Posteingang des von Outlook verwalteten IMAP-Kontos (typischerweise
                                mit der E-Mail-Adresse benannt). Wiederholen Sie dies immer in
                                Bl&ouml;cken von ca. 1000 f&uuml;r die restlichen E-Mails.</p><p>Wenn Sie versuchen zu viele E-Mails auf einmal in ein IMAP-Konto
                                zu verschieben, wird Outlook erfahrungsgem&auml;&szlig; instabil und kann
                                abst&uuml;rzen. Daher ist ein blockweises Verschieben notwendig.</p></li></ol></div></li><li><p>&Ouml;ffnen Sie den n&auml;chsten E-Mail-Ordner der zu importierenden
                        Datendatei.</p></li><li><p>Schauen Sie in der Statuszeile unten links nach der Anzahl der E-Mails.
                        Pr&uuml;fen Sie ob der Ordner weitere Unterordner enth&auml;lt. Wenn ja, dann addieren
                        sich die Zahlen der E-Mails aller Unterordner.</p><div class="orderedlist"><ol type="a"><li><p>Wenn es sich um weniger als 1000 Elemente handelt, k&ouml;nnen Sie den
                                gesamten Ordner per Drag &amp; Drop in das von Outlook verwaltete
                                IMAP-Konto (typischerweise mit der E-Mail-Adresse benannt)
                                verschieben.</p></li><li><p>Wenn es sich um mehr als 1000 Elemente handelt, legen Sie zuerst
                                den entsprechenden Ordner im von Outlook verwalteten IMAP-Konto an.
                                Markieren Sie dann die ersten ca. 1000 E-Mails. Sie k&ouml;nnen die
                                markierte Anzahl anhand der Gr&ouml;&szlig;e des Scrollbalkens rechts und der
                                Gesamtanzahl absch&auml;tzen. Verschieben Sie diese 1000 E-Mails dann per
                                Drag &amp; Drop in den entsprechenden Ordner des von Outlook
                                verwalteten IMAP-Kontos (typischerweise mit der E-Mail-Adresse
                                benannt). Wiederholen Sie dies immer in Bl&ouml;cken von ca. 1000 f&uuml;r die
                                restlichen E-Mails.</p><p>Wenn Sie versuchen zu viele E-Mails oder zu komplexe
                                Ordnerstrukturen auf einmal in ein IMAP-Konto zu verschieben, wird
                                Outlook erfahrungsgem&auml;&szlig; instabil und kann abst&uuml;rzen. Daher ist ein
                                blockweises Verschieben notwendig.</p></li></ol></div></li></ol></div></div><div class="sect2" lang="de"><div class="titlepage"><div><div><h3 class="title"><a name="groupware-client-account-import-closepst"></a>20.3.4. Datendatei schlie&szlig;en</h3></div></div></div><p>Nachdem die Daten erfolgreich von der bisherigen Datendatei &uuml;bernommen wurden,
                sollte sie wieder aus dem Profil entfernt werden um den Benutzer nicht zu
                verwirren.</p><p>Klicken Sie dazu mit der rechten Maustaste auf den Wurzelordner der Datendatei und
                w&auml;hlen <span class="guimenuitem">Outlook-Datendatei schlie&szlig;en</span>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/import-close.png"></div></div><a class="indexterm" name="d0e7134"></a><a class="indexterm" name="d0e7135"></a><a class="indexterm" name="d0e7136"></a></div></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="groupware-client-account-email.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="groupware-client-account.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="groupware-client-access.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">20.2. IMAP E-Mail-Konto&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;21. Kapitel - Freigaben und Zugriff auf fremde Ordner</td></tr></table></div>
      
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