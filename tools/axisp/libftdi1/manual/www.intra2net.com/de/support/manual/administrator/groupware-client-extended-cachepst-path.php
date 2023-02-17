<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Festlegen des Speicherorts f&uuml;r IMAP-Cache-PSTs | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="groupware-client-extended.php" title="22. Kapitel - Erweiterte Funktionen"><link rel="prev" href="groupware-client-extended-reminder.php" title="22.11. Erinnerungen in gemeinsam genutzten Ordnern"><link rel="next" href="groupware-client-extended-userdefined.php" title="22.13. Benutzerdefinierte Felder in Kontakten">
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

<a href="groupware-client-extended-cachepst-path.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="groupware-client-extended-cachepst-path.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

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

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">22.12. Festlegen des Speicherorts f&uuml;r IMAP-Cache-PSTs</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="groupware-client-extended-reminder.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">22. Kapitel - Erweiterte Funktionen</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="groupware-client-extended-userdefined.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="groupware-client-extended-cachepst-path"></a>22.12. Festlegen des Speicherorts f&uuml;r IMAP-Cache-PSTs</h2></div></div></div><a class="indexterm" name="groupware-client-extended-cachepst-path1"></a><a class="indexterm" name="groupware-client-extended-cachepst-path2"></a><p>Outlook legt f&uuml;r jedes konfigurierte IMAP-Konto auf dem PC eine .pst-Datei an um
            Ordnerstruktur, Kopfzeilen und Nachrichten lokal zwischenzuspeichern (Cache). Der genaue
            Speicherort dieser Dateien h&auml;ngt von der verwendeten Version von Windows und Outlook
            ab.</p><a class="indexterm" name="groupware-client-extended-cachepst-path3"></a><p>M&ouml;chte man den Speicherort &auml;ndern, so kann man dies &uuml;ber einen Eintrag in der
            Registrierung unter folgendem Schl&uuml;ssel festlegen:</p><p><code class="filename">HKCU\Software\Microsoft\Office\<em class="replaceable"><code>nn.n</code></em>\Outlook</code>
            Verwenden Sie statt <em class="replaceable"><code>nn</code></em> die interne Version von Outlook
                (<strong class="userinput"><code>12.0</code></strong> f&uuml;r Outlook 2007, <strong class="userinput"><code>14.0</code></strong> f&uuml;r
            Outlook 2010 und <strong class="userinput"><code>15.0</code></strong> f&uuml;r Outlook 2013).</p><p>Legen Sie in diesem Schl&uuml;ssel eine Zeichenkette mit dem Namen
                <strong class="userinput"><code>ForcePSTPath</code></strong> an. Darin k&ouml;nnen Sie dann den neuen Zielpfad
            angeben, z.B. <strong class="userinput"><code> C:\Users\%username%\AppData\Roaming</code></strong>.</p><p>Dieser Eintrag wird nur ausgewertet w&auml;hrend ein neues IMAP-Konto angelegt wird.
            Bestehende Konten werden nicht ver&auml;ndert. Der Eintrag in der Registrierung muss also vor
            dem Konfigurieren des Profils bereits angelegt sein.</p><a class="indexterm" name="d0e8212"></a><p>Beachten Sie, dass Microsoft davon abr&auml;t, .pst-Dateien auf Netzwerklaufwerken
            abzulegen. .pst-Dateien sind Datenbanken und m&uuml;ssen als solche gewisse Funktionen
            garantieren. Da aber auf einem Netzwerklaufwerk nicht alle Schutzmechanismen eines
            lokalen Laufwerks verf&uuml;gbar sind, kann die .pst-Datei nicht alle geforderten Garantien
            geben. Verletzt man diese Anforderungen, kann dies daher St&ouml;rungen und Datenverlust,
            inkl. schleichendem, erst deutlich sp&auml;ter erkennbarem, Datenverlust, zur Folge
            haben.</p><div class="note" style="margin-left: 0.2in; margin-right: 0.5in;"><table border="0" summary="Note"><tr><td rowspan="2" align="center" valign="top" width="25"><img alt="[Hinweis]" src="../images/admon/note.png"></td><th align="left">Hinweis</th></tr><tr><td align="left" valign="top"><p>Wird der Intra2net Groupware Client von Benutzern mit Servergespeicherten Profilen
                    (<span class="foreignphrase"><em class="foreignphrase">Roaming Profiles</em></span>) eingesetzt, muss die
                IMAP-Cache-PST im Verzeichnis des Servergespeicherten Profils liegen. Ansonsten kann
                Outlook die Datei beim Wechsel des PCs nicht laden.</p></td></tr></table></div><a class="indexterm" name="d0e8221"></a><a class="indexterm" name="d0e8222"></a></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="groupware-client-extended-reminder.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="groupware-client-extended.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="groupware-client-extended-userdefined.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">22.11. Erinnerungen in gemeinsam genutzten Ordnern&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;22.13. Benutzerdefinierte Felder in Kontakten</td></tr></table></div>
      
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