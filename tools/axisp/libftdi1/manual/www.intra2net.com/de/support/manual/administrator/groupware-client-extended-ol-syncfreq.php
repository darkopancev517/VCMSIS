<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Synchronisationsfrequenz von E-Mails konfigurieren | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="groupware-client-extended.php" title="22. Kapitel - Erweiterte Funktionen"><link rel="prev" href="groupware-client-extended-servermenu.php" title="22.5. Serverseitige Einstellungen in Outlook bearbeiten"><link rel="next" href="groupware-client-extended-freebusy.php" title="22.7. Frei-/Gebucht-Informationen verwenden">
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

<a href="groupware-client-extended-ol-syncfreq.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="groupware-client-extended-ol-syncfreq.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">22.6. Synchronisationsfrequenz von E-Mails konfigurieren</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="groupware-client-extended-servermenu.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">22. Kapitel - Erweiterte Funktionen</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="groupware-client-extended-freebusy.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="groupware-client-extended-ol-syncfreq"></a>22.6. Synchronisationsfrequenz von E-Mails konfigurieren</h2></div></div></div><a class="indexterm" name="groupware-client-extended-ol-syncfreq1"></a><a class="indexterm" name="groupware-client-extended-ol-syncfreq2"></a><a class="indexterm" name="groupware-client-extended-ol-syncfreq3"></a><a class="indexterm" name="groupware-client-extended-ol-syncfreq4"></a><p>Mit den folgenden Schritten k&ouml;nnen Sie einstellen, wie h&auml;ufig Outlook die
            E-Mail-Ordner auf neue Nachrichten und andere &Auml;nderungen &uuml;berpr&uuml;ft.</p><div class="note" style="margin-left: 0.2in; margin-right: 0.5in;"><table border="0" summary="Note"><tr><td rowspan="2" align="center" valign="top" width="25"><img alt="[Hinweis]" src="../images/admon/note.png"></td><th align="left">Hinweis</th></tr><tr><td align="left" valign="top"><p>Diese Einstellungen betreffen nur Ordner, die &uuml;ber die in Outlook integrierte
                IMAP-Funktionalit&auml;t synchronisiert werden. Wie Sie die Synchronisationsfrequenz von
                Ordnern, die &uuml;ber den Intra2net Groupware Client synchronisiert werden, &auml;ndern, wird
                im <a xmlns:d="http://docbook.org/ns/docbook" xmlns:xlink="http://www.w3.org/1999/xlink" href="groupware-client-extended-folderoptions.php">Abschnitt&nbsp;22.4, &#8222;Ordneroptionen&#8220;</a> erkl&auml;rt.</p></td></tr></table></div><div class="procedure"><ol type="1"><li><p>&Ouml;ffnen Sie in der Registerkarte <span class="guimenu">Senden/Empfangen</span> das Men&uuml;
                        <span class="guisubmenu">Senden-Empfangen-Gruppen&nbsp;&gt;&nbsp;Senden-Empfangen-Gruppen
                        definieren</span>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/config-imap-syncfreq01.png"></div></div><p>In Outlook 2007 ist dieses Men&uuml; erreichbar unter
                        <span class="guimenu">Extras&nbsp;&gt;&nbsp;Senden/Empfangen&nbsp;&gt;&nbsp;&Uuml;bermittlungseinstellungen&nbsp;&gt;&nbsp;Senden-Empfangen-Gruppen
                        definieren</span>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/config-imap-syncfreq01-ol2007.png"></div></div></li><li><p>Markieren Sie die Gruppe <span class="guilabel">Alle Konten</span>. Kontrollieren Sie,
                    dass die Einstellung f&uuml;r die automatische &Uuml;bermittlung auf <strong class="userinput"><code>30
                        Minuten</code></strong> steht. Klicken Sie dann auf
                        <span class="guibutton">Bearbeiten</span>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/config-imap-syncfreq02.png"></div></div></li><li><p>Stellen Sie den Nachrichtenempfang auf <span class="guilabel">Kopfzeilen f&uuml;r abonnierte
                        Ordner herunterladen</span>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/config-imap-syncfreq03.png"></div></div><p>Durch diese Einstellung werden von den normalen E-Mail-Ordnern nur noch die
                    Kopfzeilen in der lokalen Cache-PST gespeichert. Der Inhalt der E-Mails wird nur
                    bei Bedarf vom Server geladen. Dadurch verringert sich die Gr&ouml;&szlig;e der lokalen
                    Cache-PST wesentlich. Dies schont Ressourcen auf dem Client und beschleunigt das
                    Reaktionsverhalten von Outlook. </p></li><li><p>Schlie&szlig;en Sie die Gruppenkonfiguration und legen eine neue Gruppe an.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/config-imap-syncfreq04.png"></div></div></li><li><p>Nennen Sie die neue Gruppe <strong class="userinput"><code>Posteingang</code></strong>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/config-imap-syncfreq05.png"></div></div></li><li><p>Stellen Sie den Nachrichtenempfang auf <span class="guilabel">benutzerdefiniert</span>.
                    Markieren Sie dann nur den Ordner Posteingang und schalten auf <span class="guilabel">Element
                        samt Anlagen herunterladen</span>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/config-imap-syncfreq06.png"></div></div></li><li><p>Schlie&szlig;en Sie die Gruppenkonfiguration. Stellen Sie die automatische
                    &Uuml;bermittlung f&uuml;r die Gruppe <span class="guilabel">Posteingang</span> z.B. auf
                        <strong class="userinput"><code>1 Minute</code></strong>.</p><div class="screenshot"><div class="mediaobject"><img src="../images/groupware-client/config-imap-syncfreq07.png"></div></div></li></ol></div><div class="caution" style="margin-left: 0.2in; margin-right: 0.5in;"><table border="0" summary="Caution"><tr><td rowspan="2" align="center" valign="top" width="25"><img alt="[Achtung]" src="../images/admon/caution.png"></td><th align="left">Achtung</th></tr><tr><td align="left" valign="top"><p>Das Synchronisieren von vielen Ordnern erzeugt eine deutliche Belastung auf dem
                Server. Achten Sie daher unbedingt darauf, dass nur ein oder sehr wenige Ordner pro
                Benutzer mit kurzem Zeitabstand synchronisiert werden. Werden alle Ordner im Takt
                von wenigen Minuten synchronisiert, so kann der Server bereits von wenigen Benutzern
                &uuml;berlastet werden.</p></td></tr></table></div><a class="indexterm" name="d0e7882"></a><a class="indexterm" name="d0e7883"></a><a class="indexterm" name="d0e7884"></a><a class="indexterm" name="d0e7885"></a></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="groupware-client-extended-servermenu.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="groupware-client-extended.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="groupware-client-extended-freebusy.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">22.5. Serverseitige Einstellungen in Outlook bearbeiten&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;22.7. Frei-/Gebucht-Informationen verwenden</td></tr></table></div>
      
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